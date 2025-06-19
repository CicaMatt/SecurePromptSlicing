import ctypes

class Person :
    def __init__(self, name, age):
        self.name = name
        self.age = age
        self.status = 0
        
person = Person('John', 27)
print(person.name)
print(person.age)
print(person.status)