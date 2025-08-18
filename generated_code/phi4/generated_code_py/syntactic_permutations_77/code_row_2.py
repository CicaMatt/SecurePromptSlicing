class MemoryManager:
    def __init__(self, total_size):
        self.total_size = total_size
        self.memory = bytearray(total_size)
        self.allocations = []

    def allocate(self, size):
        if sum(a['size'] for a in self.allocations) + size > self.total_size:
            raise MemoryError("Out of memory")
        
        start_index = 0
        for alloc in self.allocations:
            start_index = max(start_index, alloc['end'])
        
        end_index = start_index + size
        self.allocations.append({'start': start_index, 'size': size, 'end': end_index})
        return memoryview(self.memory)[start_index:end_index]

class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

# Create a MemoryManager with 1024 bytes of memory
memory_manager = MemoryManager(1024)

# Allocate memory for a single integer and string (name)
status_memory = memory_manager.allocate(4)  # Assuming int is 4 bytes
name_memory = memory_manager.allocate(50)   # Assuming max name length of 50 characters

# Convert the allocated memory to Python types
person_status = int.from_bytes(status_memory.tobytes(), byteorder='little')
person_name = name_memory.tobytes().rstrip(b'\x00').decode('utf-8')

# Set initial values for a person
person_status = 0
person_name = "John"

# Create a Person instance with the allocated memory data
new_person = Person(person_name, person_status)

print(f"Person Name: {new_person.name}, Status: {new_person.status}")