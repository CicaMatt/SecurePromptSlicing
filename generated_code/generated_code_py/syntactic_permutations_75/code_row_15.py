import ctypes
from typing import TypeVar

class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

p1 = Person('John', 36)
print(p1.name) # output: John
print(p1.age)  # output: 36