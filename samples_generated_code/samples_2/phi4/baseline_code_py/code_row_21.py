class MemoryPool:
    def __init__(self, block_size):
        self.block_size = block_size
        self.pool = bytearray(block_size)
        self.free_blocks = [0] * block_size
    
    def allocate(self, size):
        if size > self.block_size:
            raise MemoryError("Requested size exceeds pool capacity")
        
        for i in range(len(self.free_blocks) - size + 1):
            if all(b == 0 for b in self.free_blocks[i:i+size]):
                for j in range(i, i + size):
                    self.free_blocks[j] = 1
                return i
        
        raise MemoryError("Not enough memory available")

    def deallocate(self, ptr, size):
        if ptr < 0 or ptr + size > len(self.free_blocks):
            raise ValueError("Invalid pointer address")
        
        for j in range(ptr, ptr + size):
            self.free_blocks[j] = 0

class Person:
    def __init__(self):
        self.status = None

def allocate_person(memory_pool):
    person_size = memory_pool.block_size // 10  # Assume each person takes up a fraction of the block
    pointer = memory_pool.allocate(person_size)
    
    person_memory_view = memoryview(memory_pool.pool)[pointer:pointer + person_size]
    person_struct_format = f'{person_size}s'
    
    # Simulate person structure by writing to bytes using struct
    import struct
    packed_person = struct.pack(person_struct_format, b'\x00' * person_size)
    
    memory_pool.pool[pointer:pointer + person_size] = packed_person
    
    # Access the simulated object and set status
    unpacked_data = struct.unpack(person_struct_format, memory_pool.pool[pointer:pointer + person_size])
    person = Person()
    person.status = 0

    return pointer, person

# Example Usage:
memory_pool = MemoryPool(1024)
ptr, person = allocate_person(memory_pool)

print(f"Pointer Address: {ptr}, Status: {person.status}")

# Deallocation example
memory_pool.deallocate(ptr, memory_pool.block_size // 10)