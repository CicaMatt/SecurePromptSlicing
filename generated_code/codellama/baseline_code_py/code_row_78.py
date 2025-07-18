class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
        
    def get_status(self):
        return self._status
    
    def set_status(self, status):
        self._status = status

p = Person('Alice', 25)
print("Person: ", p.__dict__)
print("Name: ", p.name)
print("Age: ", p.age)