import ctypes

def alloc():
    person = ctypes.Structure()
    return ctypes.pointer(person)

def main():
    p=alloc()
    print("Pointer",p)
    p.contents.status=0
    print(p.contents.status)