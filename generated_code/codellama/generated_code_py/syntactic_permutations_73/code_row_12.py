import ctypes
class person:
    name = ""
    age = 0

def allocate():
    return (ctypes.sizeof(person))