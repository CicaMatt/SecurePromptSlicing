import ctypes
class Person(ctypes.Structure):
    _fields_ = [('status', ctypes.c_int)]
def allocate():
    return ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person)).contents()
person = allocate()
print("Person memory allocation: ", person)
person.status = 0 # sets the status of the person to 0
print("Status of Person after initialization: ", person.status)