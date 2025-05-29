import tkinter as tk
from tkinter import ttk, filedialog

class View(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Application Tkinter")
        self.geometry("1200x600")
        self.create_widgets()
        self.create_pagination_controls()

    def create_widgets(self):
        self.menu_bar = tk.Menu(self)
        self.config(menu=self.menu_bar)
        self.file_menu = tk.Menu(self.menu_bar, tearoff=0)
        self.file_menu.add_command(label="Load", command=self.on_load)
        self.file_menu.add_command(label="Save", command=self.on_save)
        self.menu_bar.add_cascade(label="File", menu=self.file_menu)
        
        self.toolbar = tk.Frame(self, bd=1, relief=tk.RAISED)
        self.btn_add = tk.Button(self.toolbar, text="Add")
        self.btn_add.pack(side=tk.LEFT, padx=2, pady=2)
        self.btn_search = tk.Button(self.toolbar, text="Search")
        self.btn_search.pack(side=tk.LEFT, padx=2, pady=2)
        self.btn_delete = tk.Button(self.toolbar, text="Delete")
        self.btn_delete.pack(side=tk.LEFT, padx=2, pady=2)
        self.toolbar.pack(side=tk.TOP, fill=tk.X)
        
        self.tree = ttk.Treeview(self, columns=("FIO", "Address", "Birth Date", "Admission Date", "Doctor", "Conclusion"), show="headings")
        for col in ("FIO", "Address", "Birth Date", "Admission Date", "Doctor", "Conclusion"):
            self.tree.heading(col, text=col)
        self.tree.pack(expand=True, fill=tk.BOTH)

    def create_pagination_controls(self):
        pagination_frame = tk.Frame(self)
        pagination_frame.pack(side=tk.BOTTOM, fill=tk.X, pady=5)
        
        self.btn_first = tk.Button(pagination_frame, text="<< First")
        self.btn_prev = tk.Button(pagination_frame, text="< Prev")
        self.btn_next = tk.Button(pagination_frame, text="Next >")
        self.btn_last = tk.Button(pagination_frame, text="Last >>")
        
        self.lbl_page_info = tk.Label(pagination_frame, text="Page 1 of 1")
        
        self.page_size_var = tk.StringVar(value="10")
        self.page_size_menu = ttk.Combobox(pagination_frame, 
                                         textvariable=self.page_size_var,
                                         values=["5", "10", "20", "50"],
                                         state="readonly",
                                         width=5)
        
        self.btn_first.pack(side=tk.LEFT, padx=2)
        self.btn_prev.pack(side=tk.LEFT, padx=2)
        self.lbl_page_info.pack(side=tk.LEFT, padx=10)
        self.btn_next.pack(side=tk.LEFT, padx=2)
        self.btn_last.pack(side=tk.LEFT, padx=2)
        tk.Label(pagination_frame, text="Records per page:").pack(side=tk.LEFT, padx=2)
        self.page_size_menu.pack(side=tk.LEFT, padx=2)
    
    def update_table(self, records):
        self.tree.delete(*self.tree.get_children())
        for record in records:
            self.tree.insert("", "end", values=(
                record.fio, 
                record.address, 
                record.birth_date, 
                record.admission_date, 
                record.doctor, 
                record.conclusion
            ))
    
    def on_load(self):
        filename = filedialog.askopenfilename(filetypes=[("XML Files", "*.xml")])
        if filename:
            self.controller.load_from_xml(filename)  

    def on_save(self):
        self.controller.save_to_xml()

