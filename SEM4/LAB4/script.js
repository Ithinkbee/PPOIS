document.addEventListener('DOMContentLoaded', function () {
    loadSettings();

    document.getElementById('show-order-form')?.addEventListener('click', function (e) {
        e.preventDefault();
        const form = document.getElementById('order-form');
        form.style.display = form.style.display === 'none' ? 'block' : 'none';
    });

    const orderForm = document.getElementById('orderForm');
    if (orderForm) {
        orderForm.addEventListener('submit', async function (e) {
            e.preventDefault();

            const formData = new FormData(this);
            const data = {
                trader_id: formData.get('trader_id'),
                order_type: formData.get('order_type'),
                symbol: formData.get('symbol').toUpperCase(),
                quantity: parseFloat(formData.get('quantity')),
                price: parseFloat(formData.get('price'))
            };

            try {
                const response = await fetch('/place_order', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(data)
                });

                const result = await response.json();
                if (response.ok) {
                    showToast(`Order successful! ${result.message}`);
                    orderForm.reset();
                } else {
                    showToast(`Error: ${result.message || 'Unknown error'}`);
                }
            } catch (error) {
                showToast(`Network error: ${error.message}`);
            }
        });
    }

    document.getElementById('cancel-order')?.addEventListener('click', function () {
        document.getElementById('order-form').style.display = 'none';
    });

    document.getElementById('show-settings-panel')?.addEventListener('click', function (e) {
        e.preventDefault();
        const panel = document.getElementById('settings-panel');
        panel.style.display = panel.style.display === 'none' ? 'block' : 'none';
    });

    document.getElementById('cancel-settings')?.addEventListener('click', function () {
        document.getElementById('settings-panel').style.display = 'none';
    });

    document.getElementById('apply-settings')?.addEventListener('click', async function () {
        const platform = document.getElementById('platform-select').value;
        const broker = document.getElementById('broker-select').value;

        try {
            const response = await fetch('/update_settings', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ platform, broker_id: broker })
            });

            const result = await response.json();
            if (response.ok) {
                updateCurrentSettingsDisplay();
                updateCommissionDisplay();
                showToast(result.message || 'Settings updated!');
            } else {
                showToast(result.message || 'Failed to update settings');
            }
        } catch (error) {
            showToast('Network error: ' + error.message);
        }
    });

    document.getElementById('broker-select')?.addEventListener('change', updateCommissionDisplay);
});

async function loadSettings() {
    try {
        const response = await fetch('/get_current_settings');
        const settings = await response.json();

        document.getElementById('platform-select').value = settings.current_platform;
        document.getElementById('broker-select').value = settings.current_broker;

        updateCurrentSettingsDisplay();
        updateCommissionDisplay();
    } catch (error) {
        console.error('Failed to load settings:', error);
    }
}

function updateCurrentSettingsDisplay() {
    const platform = document.getElementById('platform-select').value;
    const broker = document.getElementById('broker-select').value;

    document.getElementById('current-platform-display').textContent = platform;
    document.getElementById('current-broker-display').textContent =
        `${broker} (${broker === 'B1' ? '1%' : '2%'} commission)`;
}

function updateCommissionDisplay() {
    const broker = document.getElementById('broker-select').value;
    const commission = broker === 'B1' ? '1%' : '2%';
    const commissionElement = document.getElementById('current-commission');
    if (commissionElement) {
        commissionElement.textContent = commission;
    }
}

function showToast(message) {
    const toast = document.createElement('div');
    toast.className = 'toast';
    toast.textContent = message;
    document.body.appendChild(toast);

    setTimeout(() => toast.remove(), 3000);
}

