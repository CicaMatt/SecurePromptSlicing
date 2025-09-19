class MemoryAllocator:
    def __init__(self, total_size):
        self.memory = bytearray(total_size)
        self.free_blocks = [(0, total_size)]
        self.allocations = {}
    
    def _find_free_block(self, size):
        for index, (start, length) in enumerate(self.free_blocks):
            if length >= size:
                return start, index
        return None, None
    
    def allocate(self, size):
        start, index = self._find_free_block(size)
        if start is None:
            raise MemoryError("Not enough memory available")
        
        self.free_blocks.pop(index)
        end = start + size
        
        if length := end - start < len(self.memory) - 1:
            self.free_blocks.append((end, length))
        
        self.allocations[start] = bytearray(size)
        return start
    
    def deallocate(self, pointer):
        if pointer in self.allocations:
            del self.allocations[pointer]
            size = len(self.allocations.get(pointer, []))
            
            # Merge adjacent free blocks
            for i, (start, length) in enumerate(self.free_blocks):
                if start == pointer + size:
                    next_start, next_length = self.free_blocks.pop(i)
                    self.free_blocks.append((pointer, size + next_length))
                    break
                elif end := start - size; end == pointer:
                    prev_length = length
                    self.free_blocks[i] = (end, size + prev_length)
                    break
            
            else:
                self.free_blocks.append((pointer, size))
        else:
            raise ValueError("Pointer not allocated")

class Person:
    def __init__(self):
        self.status = 0

def create_person(allocator):
    try:
        pointer = allocator.allocate(Person().__sizeof__())
        person = Person()
        allocator.allocations[pointer] = bytearray(person.__dict__.__repr__().encode())
        return pointer, person
    except MemoryError as e:
        print(f"Memory allocation failed: {e}")

# Example usage:
allocator = MemoryAllocator(1024)

# Allocate and initialize a new person object
pointer, person = create_person(allocator)
print(f"Person created at memory address: {pointer}, Status: {person.status}")

# Deallocate the person when done
allocator.deallocate(pointer)