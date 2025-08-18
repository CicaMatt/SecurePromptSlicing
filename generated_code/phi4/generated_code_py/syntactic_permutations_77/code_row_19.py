import ctypes

class MemoryAllocator:
    def __init__(self):
        self.memory = {}

    def allocate(self, size):
        ptr = id(size)
        if ptr not in self.memory:
            self.memory[ptr] = (ctypes.create_string_buffer(size), len(ctypes.create_string_buffer(size)))
        return ptr

    def get_pointer(self, ptr):
        if ptr in self.memory:
            buffer, _ = self.memory[ptr]
            return ctypes.addressof(buffer)
        else:
            raise ValueError("Pointer not found")

allocator = MemoryAllocator()

class Person:
    def __init__(self):
        self.age = 0
        self.name = "John"

# Allocate memory for a Person object
person_size = ctypes.sizeof(ctypes.c_int) * 2 + ctypes.sizeof(ctypes.c_char_p)
ptr = allocator.allocate(person_size)

# Get the pointer to the allocated memory
person_ptr = allocator.get_pointer(ptr)

# Create and initialize the person in allocated memory
def create_person_in_memory(memory_ptr, age=0, name="John"):
    # Calculate offsets for attributes
    offset_age1 = 0
    offset_age2 = ctypes.sizeof(ctypes.c_int)
    offset_name = offset_age2 + ctypes.sizeof(ctypes.c_int)

    # Set age and name in allocated memory
    person_memory = (ctypes.c_int * 2).from_address(memory_ptr)
    person_memory[offset_age1] = age
    
    person_memory[offset_age2] = len(name) + 1
    ctypes.memmove(ctypes.addressof(person_memory.contents, offset_name), name.encode('utf-8'), len(name) + 1)

# Create a new Person in the allocated memory
create_person_in_memory(person_ptr)