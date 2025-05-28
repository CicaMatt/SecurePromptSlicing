class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
    
    def set_status(self, status):
        self.status = status
    
    def get_status(self):
        return self.status
    
    def __str__(self):
        return f"Person {self.name} is {self.age}"

person = Person("John", 36)