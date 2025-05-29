from dialogs import AddRecordDialog, SearchDialog, RemovePatientsDialog, SearchResultsDialog
from tkinter import messagebox

class Controller:
    def __init__(self, model, view):
        self.model = model
        self.view = view
        self.current_filename = None 
        self.disable_actions(True)  
        self.setup()
        self.setup_pagination()

    def setup(self):
        self.view.btn_add.config(command=self.add_record)
        self.view.btn_search.config(command=self.search_record)
        self.view.btn_delete.config(command=self.delete_record)
    
    def add_record(self):
        dialog = AddRecordDialog(self.view)
        self.view.wait_window(dialog)
        if dialog.result:
            self.model.add_record(dialog.result)
            self.model.go_to_page(self.model.get_total_pages())
            self.update_pagination()

    def search_record(self):
        dialog = SearchDialog(self.view)
        self.view.wait_window(dialog)
        if dialog.result:
            results = self.model.search_records(**dialog.result)
            SearchResultsDialog(self.view, results)
    
    def delete_record(self):
        dialog = RemovePatientsDialog(self.view)
        self.view.wait_window(dialog)
        if dialog.result:
            deleted_count = self.model.remove_records(**dialog.result)
            self.model.go_to_page(min(self.model.current_page, self.model.get_total_pages()))
            self.update_pagination()

            if deleted_count > 0:
                messagebox.showinfo("Deletion Info", f"Records removed: {deleted_count}")
            else:
                messagebox.showinfo("Deletion Info", "No matching records.")

    def load_from_xml(self, filename):
        try:
            self.model.load_from_xml(filename)
            self.current_filename = filename
            self.update_pagination()
            self.disable_actions(False)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load file: {str(e)}")

    def disable_actions(self, disable):
        state = "disabled" if disable else "normal"
        print(f"Buttons: {state}") 
        self.view.btn_add.config(state=state)
        self.view.btn_search.config(state=state)
        self.view.btn_delete.config(state=state)

    def save_to_xml(self):
        if self.current_filename:
            self.model.save_to_xml(self.current_filename)
        else:
            messagebox.showwarning("Warning", "Please, load XML file!")

    def setup_pagination(self):
        self.view.btn_first.config(command=self.first_page)
        self.view.btn_prev.config(command=self.prev_page)
        self.view.btn_next.config(command=self.next_page)
        self.view.btn_last.config(command=self.last_page)
        self.view.page_size_menu.bind("<<ComboboxSelected>>", self.change_page_size)
    
    def update_pagination(self):
        total_records = len(self.model.records)
        total_pages = self.model.get_total_pages()
        current_page = self.model.current_page
        page_size = self.model.page_size
    
        start_record = (current_page - 1) * page_size + 1
        end_record = min(current_page * page_size, total_records)
    
        self.view.lbl_page_info.config(
            text=f"Page {current_page} of {total_pages} | Records: {start_record}-{end_record} of {total_records}"
        )
    
        self.view.btn_first.config(state="normal" if current_page > 1 else "disabled")
        self.view.btn_prev.config(state="normal" if current_page > 1 else "disabled")
        self.view.btn_next.config(state="normal" if current_page < total_pages else "disabled")
        self.view.btn_last.config(state="normal" if current_page < total_pages else "disabled")
    
        self.view.update_table(self.model.get_paginated_records())
    
    def first_page(self):
        self.model.go_to_page(1)
        self.update_pagination()
    
    def prev_page(self):
        self.model.go_to_page(self.model.current_page - 1)
        self.update_pagination()
    
    def next_page(self):
        self.model.go_to_page(self.model.current_page + 1)
        self.update_pagination()
    
    def last_page(self):
        self.model.go_to_page(self.model.get_total_pages())
        self.update_pagination()
    
    def change_page_size(self, event=None):
        self.model.set_page_size(self.view.page_size_var.get())
        self.update_pagination()