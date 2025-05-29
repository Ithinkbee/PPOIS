import xml.sax
from xml.dom.minidom import Document   
from patient import Patient

class PatientHandler(xml.sax.ContentHandler):
    def __init__(self):
        self.current_data = ""
        self.patient_data = {}
        self.patients = []

    def startElement(self, tag, attributes):
        self.current_data = tag

    def characters(self, content):
        if self.current_data:
            self.patient_data[self.current_data] = content.strip()

    def endElement(self, tag):
        if tag == "patient":
            self.patients.append(Patient(
                self.patient_data.get("fio", ""),
                self.patient_data.get("address", ""),
                self.patient_data.get("birth_date", ""),
                self.patient_data.get("admission_date", ""),
                self.patient_data.get("doctor", ""),
                self.patient_data.get("conclusion", "")
            ))
            self.patient_data = {}
        self.current_data = ""

class Model:
    def __init__(self):
        self.records = []
        self.current_page = 1
        self.page_size = 10

    def add_record(self, record: Patient):
        self.records.append(record)
        return self.records
        
    def search_records(self, **kwargs):
        results = [record for record in self.records if self.match(record, kwargs)]
        return results
    
    def remove_records(self, **kwargs):
        initial_count = len(self.records)
        self.records = [record for record in self.records if not self.match(record, kwargs)]
        removed_count = initial_count - len(self.records)
        return removed_count
    
    def match(self, record, filters):
        for key, value in filters.items():
            if value:
                if key == "fio":  
                    record_surname = record.fio.split()[0] if record.fio else ""
                    if record_surname.lower() != value.lower():
                        return False
                elif key == "address":  
                    if record.address.lower() != value.lower():
                        return False
                elif key == "doctor": 
                    if value.lower() not in record.doctor.lower():
                        return False
                elif key == "admission_date":  
                    if str(record.admission_date) != value:  
                        return False
                else:
                    attr_value = getattr(record, key, None)
                    if attr_value is None or str(attr_value).lower() != value.lower():
                        return False
        return True

    def load_from_xml(self, filename):
        handler = PatientHandler()
        parser = xml.sax.make_parser()
        parser.setContentHandler(handler)
        parser.parse(filename)
        self.records = handler.patients  
        self.current_page = 1  

    def save_to_xml(self, filename):
        doc = Document()
        root = doc.createElement("patients")
        doc.appendChild(root)

        for record in self.records:
            patient_elem = doc.createElement("patient")

            def create_element(name, value):
                elem = doc.createElement(name)
                elem.appendChild(doc.createTextNode(value))
                return elem

            patient_elem.appendChild(create_element("fio", record.fio))
            patient_elem.appendChild(create_element("address", record.address))
            patient_elem.appendChild(create_element("birth_date", str(record.birth_date)))
            patient_elem.appendChild(create_element("admission_date", str(record.admission_date)))
            patient_elem.appendChild(create_element("doctor", record.doctor))
            patient_elem.appendChild(create_element("conclusion", record.conclusion))

            root.appendChild(patient_elem)

        with open(filename, "w", encoding="utf-8") as f:
            f.write(doc.toprettyxml(indent="  "))

    def get_paginated_records(self):
        start = (self.current_page - 1) * self.page_size
        end = start + self.page_size
        return self.records[start:end]
    
    def get_total_pages(self):
        return max(1, (len(self.records) + self.page_size - 1) // self.page_size)
    
    def set_page_size(self, size):
        self.page_size = int(size)
        self.current_page = 1  
    
    def go_to_page(self, page_num):
        total_pages = self.get_total_pages()
        self.current_page = max(1, min(page_num, total_pages))