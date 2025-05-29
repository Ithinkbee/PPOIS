from flask import Flask, request, jsonify, Response
from flask_cors import CORS
from exchange import Exchange
from broker import Broker
from trader import Trader
from currency import Currency
from stock import Stock
import os

app = Flask(__name__)
CORS(app)

def init_system(platform="Platform 1"): 
    exchange = Exchange()
    
    current_platform = platform  

    if current_platform == "Platform 1":
        usd = Currency("USD", "US Dollar", 1.0, 1000000)
        eur = Currency("EUR", "Euro", 1.1, 500000)
        apple = Stock("AAPL", "Apple Inc.", 150.0, 0.02, 10000)
        google = Stock("GOOGL", "Alphabet Inc.", 2800.0, 0.0, 5000)
    else:  
        usd = Currency("USD", "US Dollar", 1.05, 1200000)
        eur = Currency("EUR", "Euro", 1.15, 600000)
        apple = Stock("AAPL", "Apple Inc.", 160.0, 0.02, 12000)
        google = Stock("GOOGL", "Alphabet Inc.", 2850.0, 0.0, 5500)
    
    exchange.add_instrument(usd)
    exchange.add_instrument(eur)
    exchange.add_instrument(apple)
    exchange.add_instrument(google)
    
    broker1 = Broker("B1", 0.01, exchange)
    broker2 = Broker("B2", 0.02, exchange)
    
    trader1 = Trader("T1", 10000000.0)
    trader2 = Trader("T2", 10000000.0)
    trader2.add_to_portfolio(usd, 1000000)
    trader2.add_to_portfolio(eur, 100000)
    trader2.add_to_portfolio(apple, 1000)
    trader2.add_to_portfolio(google, 100)
    
    return {
        'exchange': exchange,
        'brokers': [broker1, broker2],
        'traders': [trader1, trader2],
        'current_broker': broker1,
        'current_trader': trader1,
        'current_platform': current_platform
    }

system_data = init_system()

def serve_file(filename, content_type='text/html'):
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            return Response(f.read(), content_type=content_type)
    except FileNotFoundError:
        return Response("File not found", status=404)

@app.route('/')
def index():
    return serve_file('index.html')

@app.route('/market_data')
def market_data():
    try:
        with open('market_data.html', 'r', encoding='utf-8') as f:
            template = f.read()
            
        instruments = system_data['exchange'].instruments
        
        instruments_html = "\n".join(
            f"<tr><td>{instr.symbol}</td><td>{instr.current_price}</td><td>{instr.volume}</td></tr>"
            for instr in instruments
        )
        
        content = template.replace('<!-- INSTRUMENTS_ROWS -->', instruments_html)
        
        return Response(content, content_type='text/html')
    except FileNotFoundError:
        return Response("Market data template not found", status=404)

@app.route('/trader_report/<trader_id>')
def trader_report(trader_id):
    trader = next((t for t in system_data['traders'] if t.trader_id == trader_id), None)
    if not trader:
        return Response("Trader not found", status=404)
    
    try:
        with open('trader_report.html', 'r', encoding='utf-8') as f:
            content = f.read()
            
        portfolio_value = sum(
            instr.current_price * trader.get_instrument_quantity(instr) 
            for instr in system_data['exchange'].instruments
        )
        
        trade_history = "\n".join(
            f"Order ID: {order.order_id}\n"
            f"Type: {order.order_type}\n"
            f"Instrument: {order.instrument.symbol}\n"
            f"Quantity: {order.quantity}\n"
            f"Price: {order.price}\n"
            f"Status: {order.status}\n" + "-"*40
            for order in trader.trade_history
        )
        
        content = content.replace('<!-- TRADER_ID -->', trader_id)
        content = content.replace('<!-- BALANCE -->', f"{trader.get_balance():.2f}")
        content = content.replace('<!-- PORTFOLIO_VALUE -->', f"{portfolio_value:.2f}")
        content = content.replace('<!-- TRADE_HISTORY -->', trade_history)
        
        return Response(content, content_type='text/html')
    except FileNotFoundError:
        return Response("Trader report template not found", status=404)

@app.route('/style.css')
def serve_css():
    try:
        with open('style.css', 'r', encoding='utf-8') as f:
            return Response(f.read(), content_type='text/css')
    except FileNotFoundError:
        return Response("CSS not found", status=404)

@app.route('/script.js')
def serve_js():
    try:
        with open('script.js', 'r', encoding='utf-8') as f:
            return Response(f.read(), content_type='application/javascript')
    except FileNotFoundError:
        return Response("JS not found", status=404)

@app.route('/place_order', methods=['POST'])
def place_order():
    try:
        data = request.get_json()
        if not data:
            return jsonify({'status': 'error', 'message': 'No data provided'}), 400

        trader = next((t for t in system_data['traders'] if t.trader_id == data['trader_id']), None)
        instrument = next((i for i in system_data['exchange'].instruments 
                         if i.symbol == data['symbol']), None)
        
        if not trader:
            return jsonify({'status': 'error', 'message': 'Trader not found'}), 404
        if not instrument:
            return jsonify({'status': 'error', 'message': 'Instrument not found'}), 404

        try:
            quantity = float(data['quantity'])
            price = float(data['price'])
        except (ValueError, TypeError):
            return jsonify({'status': 'error', 'message': 'Invalid quantity or price format'}), 400

        if data['order_type'] == 'buy':
            trader.buy(system_data['current_broker'], instrument, quantity, price)
        else:
            trader.sell(system_data['current_broker'], instrument, quantity, price)
        
        return jsonify({
            'status': 'success',
            'message': 'Order placed successfully',
            'new_balance': trader.get_balance()
        })
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/get_current_settings')
def get_current_settings():
    return jsonify({
        'current_platform': system_data['current_platform'],
        'current_broker': system_data['current_broker'].broker_id
    })

@app.route('/update_settings', methods=['POST'])
def update_settings():
    data = request.json
    platform = data.get('platform')
    broker_id = data.get('broker_id')
    
    if platform in ['Platform 1', 'Platform 2']:
        system_data.update(init_system(platform))  
        system_data['current_platform'] = platform
    
    broker = next((b for b in system_data['brokers'] if b.broker_id == broker_id), None)
    if broker:
        system_data['current_broker'] = broker
    
    return jsonify({
        'status': 'success',
        'message': f"Switched to {platform}, broker {broker_id}"
    })

if __name__ == '__main__':
    required_files = ['index.html', 'market_data.html', 'trader_report.html']
    for file in required_files:
        if not os.path.exists(file):
            print(f"Warning: {file} not found in current directory")
    
    app.run(debug=True)