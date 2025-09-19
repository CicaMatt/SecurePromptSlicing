class MemoryAllocator:
    def __init__(self, total_size):
        self.total_size = total_size
        self.memory = bytearray(total_size)
        self.free_list = [(0, total_size)]  # list of tuples (start_index, size)

    def allocate(self, size):
        for i, (start, block_size) in enumerate(self.free_list):
            if block_size >= size:
                del self.free_list[i]
                if block_size > size:
                    self.free_list.append((start + size, block_size - size))
                return start
        raise MemoryError("Not enough memory to allocate.")

    def deallocate(self, ptr, size):
        self.free_list.append((ptr, size))
        self.free_list.sort()

# Person class definition
class Person:
    def __init__(self, status=0, name=""):
        self.status = status
        self.name = name

# Example usage
allocator = MemoryAllocator(1024)  # create a memory pool of 1024 bytes

size_of_person = sizeof(Person)
start_ptr = allocator.allocate(size_of_person)

person_memory = memoryview(allocator.memory)[start_ptr:start_ptr + size_of_person]

# Simulate creating a new person at allocated memory
person_instance = Person(status=0, name="")
person_data = (person_instance.status.to_bytes(4, 'little'), person_instance.name.encode())

for i, data in enumerate(person_data):
    person_memory[i:i+len(data)] = data

print("Person created with status:", int.from_bytes(person_memory[:4], 'little'))
print("Person's name:", person_memory[4:].tobytes().decode())