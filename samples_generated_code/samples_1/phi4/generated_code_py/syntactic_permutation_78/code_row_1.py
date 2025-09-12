import ctypes

class Person:
    def __init__(self):
        self.status = 0

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def create_person():
    person = Person()
    return ctypes.pointer(ctypes.py_object(person))

# Example usage
if __name__ == "__main__":
    # Allocate a block of memory for 100 bytes
    memory_block = allocate_memory(100)
    
    # Create a new person and get pointer to the person object
    person_pointer = create_person()
    print(f"Memory address: {memory_block}")
    print(f"Person status: {person_pointer.contents.status}")