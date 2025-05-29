import tkinter as tk
from tkinter import ttk, messagebox
from patient import Patient
import datetime

class BaseDialog(tk.Toplevel):
    def __init__(self, parent, title):
        super().__init__(parent)
        self.title(title)
        self.result = None
        
    def create_entry(self, label_text, row):
        tk.Label(self, text=label_text).grid(row=row, column=0)
        entry = tk.Entry(self, width=40) 
        entry.grid(row=row, column=1)
        return entry

class AddRecordDialog(BaseDialog):
    def __init__(self, parent):
        super().__init__(parent, "Add Record")
        
        self.fio_entry = self.create_entry("Full Name:", 0)
        self.address_entry = self.create_entry("Address:", 1)
        self.birth_entry = self.create_entry("Birth Date (YYYY-MM-DD):", 2)
        self.admission_entry = self.create_entry("Admission Date (YYYY-MM-DD):", 3)
        self.doctor_entry = self.create_entry("Doctor:", 4)
        self.conclusion_entry = self.create_entry("Conclusion:", 5)
        
        tk.Button(self, text="Add", command=self.on_add).grid(row=6, column=0)
        tk.Button(self, text="Cancel", command=self.destroy).grid(row=6, column=1)
    
    def on_add(self):
        try:
            patient = Patient(
                self.fio_entry.get(),
                self.address_entry.get(),
                datetime.datetime.strptime(self.birth_entry.get(), "%Y-%m-%d").date(),
                datetime.datetime.strptime(self.admission_entry.get(), "%Y-%m-%d").date(),
                self.doctor_entry.get(),
                self.conclusion_entry.get()
            )
            self.result = patient
            self.destroy()
        except ValueError:
            messagebox.showerror("Error", "Invalid date format. Use YYYY-MM-DD.")

class SearchResultsDialog(tk.Toplevel):
    def __init__(self, parent, results):
        super().__init__(parent)
        self.title("Search Results")
        self.results = results
        self.current_page = 1
        self.page_size = 10
        
        if not results:
            tk.Label(self, text="Not found", font=("Arial", 12)).pack(pady=10)
            tk.Button(self, text="OK", command=self.destroy).pack(pady=5)
            return
        
        self.tree = ttk.Treeview(self, columns=("FIO", "Address", "Birth Date", "Admission Date", "Doctor", "Conclusion"), show="headings")
        for col in ("FIO", "Address", "Birth Date", "Admission Date", "Doctor", "Conclusion"):
            self.tree.heading(col, text=col)
        self.tree.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)
        
        self.create_pagination_controls()
        self.update_results_table()
    
    def create_pagination_controls(self):
        pagination_frame = tk.Frame(self)
        pagination_frame.pack(side=tk.BOTTOM, fill=tk.X, pady=5)
        
        self.btn_first = tk.Button(pagination_frame, text="<< First", command=self.first_page)
        self.btn_prev = tk.Button(pagination_frame, text="< Prev", command=self.prev_page)
        self.btn_next = tk.Button(pagination_frame, text="Next >", command=self.next_page)
        self.btn_last = tk.Button(pagination_frame, text="Last >>", command=self.last_page)
        
        self.lbl_page_info = tk.Label(pagination_frame)
        
        self.page_size_var = tk.StringVar(value=str(self.page_size))
        self.page_size_menu = ttk.Combobox(pagination_frame, 
                                         textvariable=self.page_size_var,
                                         values=["5", "10", "20", "50"],
                                         state="readonly",
                                         width=5)
        self.page_size_menu.bind("<<ComboboxSelected>>", self.change_page_size)
        
        self.btn_first.pack(side=tk.LEFT, padx=2)
        self.btn_prev.pack(side=tk.LEFT, padx=2)
        self.lbl_page_info.pack(side=tk.LEFT, padx=10)
        self.btn_next.pack(side=tk.LEFT, padx=2)
        self.btn_last.pack(side=tk.LEFT, padx=2)
        tk.Label(pagination_frame, text="Records per page:").pack(side=tk.LEFT, padx=2)
        self.page_size_menu.pack(side=tk.LEFT, padx=2)
    
    def get_paginated_results(self):
        start = (self.current_page - 1) * self.page_size
        end = start + self.page_size
        return self.results[start:end]
    
    def get_total_pages(self):
        return max(1, (len(self.results) + self.page_size - 1) // self.page_size)
    
    def update_results_table(self):
        self.tree.delete(*self.tree.get_children())
        
        for record in self.get_paginated_results():
            self.tree.insert("", "end", values=(
                record.fio, 
                record.address, 
                record.birth_date, 
                record.admission_date, 
                record.doctor, 
                record.conclusion
            ))
        
        total_records = len(self.results)
        total_pages = self.get_total_pages()
        start_record = (self.current_page - 1) * self.page_size + 1
        end_record = min(self.current_page * self.page_size, total_records)
        
        self.lbl_page_info.config(
            text=f"Page {self.current_page} of {total_pages} | Records: {start_record}-{end_record} of {total_records}"
        )
        
        self.btn_first.config(state="normal" if self.current_page > 1 else "disabled")
        self.btn_prev.config(state="normal" if self.current_page > 1 else "disabled")
        self.btn_next.config(state="normal" if self.current_page < total_pages else "disabled")
        self.btn_last.config(state="normal" if self.current_page < total_pages else "disabled")
    
    def change_page_size(self, event=None):
        self.page_size = int(self.page_size_var.get())
        self.current_page = 1 
        self.update_results_table()
    
    def first_page(self):
        self.current_page = 1
        self.update_results_table()
    
    def prev_page(self):
        self.current_page = max(1, self.current_page - 1)
        self.update_results_table()
    
    def next_page(self):
        self.current_page = min(self.get_total_pages(), self.current_page + 1)
        self.update_results_table()
    
    def last_page(self):
        self.current_page = self.get_total_pages()
        self.update_results_table()

class SearchDialog(BaseDialog):
    def __init__(self, parent, title="Searching"):
        super().__init__(parent, title)
        
        self.search_type = tk.StringVar(value="surname_address")
        options = ["surname_address", "birth_date", "doctor_admission"]
        tk.Label(self, text="Search by:").grid(row=0, column=0)
        self.search_menu = ttk.Combobox(self, values=options, textvariable=self.search_type)
        self.search_menu.grid(row=0, column=1)
        self.search_menu.bind("<<ComboboxSelected>>", self.update_fields)
        
        self.search_entry = self.create_entry("Value:", 1)
        
        tk.Button(self, text="Search", command=self.on_search).grid(row=2, column=0)
        tk.Button(self, text="Cancel", command=self.destroy).grid(row=2, column=1)
    
    def update_fields(self, event):
        self.search_entry.delete(0, tk.END)
    
    def on_search(self):
        value = self.search_entry.get().strip()
        
        if self.search_type.get() == "surname_address":
            if any(char.isdigit() for char in value):  
                self.result = {"address": value}
            else: 
                self.result = {"fio": value}
        elif self.search_type.get() == "birth_date":
            self.result = {"birth_date": value}
        elif self.search_type.get() == "doctor_admission":
            if any(char.isdigit() for char in value):
                self.result = {"admission_date": value}
            else:  
                self.result = {"doctor": value}
        else:
            self.result = {}

        self.destroy()

class RemovePatientsDialog(BaseDialog):
    def __init__(self, parent):
        super().__init__(parent, "Remove Patients")
        
        self.search_type = tk.StringVar(value="surname_address")
        options = ["surname_address", "birth_date", "doctor_admission"]
        tk.Label(self, text="Remove by:").grid(row=0, column=0)
        self.search_menu = ttk.Combobox(self, values=options, textvariable=self.search_type)
        self.search_menu.grid(row=0, column=1)
        self.search_menu.bind("<<ComboboxSelected>>", self.update_fields)
        
        self.search_entry = self.create_entry("Value:", 1)
        
        tk.Button(self, text="Remove", command=self.on_remove).grid(row=2, column=0)
        tk.Button(self, text="Cancel", command=self.destroy).grid(row=2, column=1)
    
    def update_fields(self, event):
        self.search_entry.delete(0, tk.END)
    
    def on_remove(self):
        value = self.search_entry.get().strip()
        
        if self.search_type.get() == "surname_address":
            if any(char.isdigit() for char in value):  
                self.result = {"address": value}
            else:  
                self.result = {"fio": value}
        elif self.search_type.get() == "birth_date":
            self.result = {"birth_date": value}
        elif self.search_type.get() == "doctor_admission":
            if any(char.isdigit() for char in value): 
                self.result = {"admission_date": value}
            else:  
                self.result = {"doctor": value}
        else:
            self.result = {}

        self.destroy()