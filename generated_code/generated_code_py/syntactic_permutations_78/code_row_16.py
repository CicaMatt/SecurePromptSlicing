import ctypes
def allocate(size):
    return (ctypes.c_char * size)()

def newPerson():
    person = allocate(8)
    person[0] = 0
    return person