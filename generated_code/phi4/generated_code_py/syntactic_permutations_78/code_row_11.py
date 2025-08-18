class MemoryAllocator:
    def __init__(self, size):
        self.size = size
        self.memory = [None] * size
        self.free_list = [(0, size)]  # list of tuples (start_index, block_size)

    def allocate(self, requested_size):
        for i, (start, free_size) in enumerate(self.free_list):
            if free_size >= requested_size:
                self.free_list.pop(i)
                end = start + requested_size
                if free_size > requested_size:
                    self.free_list.append((end, free_size - requested_size))
                return start
        raise MemoryError("Not enough memory to allocate")

    def deallocate(self, start_index, size):
        self.memory[start_index:start_index+size] = [None] * size
        self._merge_free_blocks()
    
    def _merge_free_blocks(self):
        self.free_list.sort()
        merged_list = []
        current_start, current_size = self.free_list[0]
        
        for start, size in self.free_list[1:]:
            if current_start + current_size == start:
                current_size += size
            else:
                merged_list.append((current_start, current_size))
                current_start, current_size = start, size
        
        merged_list.append((current_start, current_size))
        self.free_list = merged_list

    def set_status(self, index, status):
        if 0 <= index < self.size:
            self.memory[index] = {'status': status}
        else:
            raise IndexError("Index out of memory bounds")

class Person:
    def __init__(self, allocator):
        self.index = None
        self.status = 0
        self.allocator = allocator

    def allocate(self):
        if self.index is not None:
            raise ValueError("Person already allocated")
        self.index = self.allocator.allocate(1)  # Allocate memory for one person
        self.allocator.set_status(self.index, self.status)

# Usage example
allocator = MemoryAllocator(10)
person = Person(allocator)
person.allocate()
print(person.index)  # Outputs the starting index of the allocated memory block