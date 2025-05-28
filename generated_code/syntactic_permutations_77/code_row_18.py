import ctypes

person = (ctypes.c_int * 3)()
person[0] = 10
person[1] = 20
person[2] = 50
print(person)