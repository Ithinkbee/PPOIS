import datetime

class Patient:
    def __init__(self, fio, address, birth_date, admission_date, doctor, conclusion):
        self.fio = fio
        self.address = address
        self.birth_date = self.parse_date(birth_date)
        self.admission_date = self.parse_date(admission_date)
        self.doctor = doctor
        self.conclusion = conclusion

    def parse_date(self, date_value):
        if isinstance(date_value, str):
            return datetime.datetime.strptime(date_value, "%Y-%m-%d").date()
        return date_value
