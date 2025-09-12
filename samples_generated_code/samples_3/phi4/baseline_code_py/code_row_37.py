class MemoryAllocator:
    def __init__(self, total_size):
        self.memory = bytearray(total_size)
        self.free_blocks = [(0, total_size)]

    def allocate(self, size):
        for index, (start, length) in enumerate(self.free_blocks):
            if length >= size:
                del self.free_blocks[index]
                end = start + size
                if length > size:
                    self.free_blocks.insert(index, (end, length - size))
                return memoryview(self.memory)[start:end]

        raise MemoryError("Not enough memory")

    def deallocate(self, block):
        start = block.obj.index(block.tobytes())
        end = start + len(block)
        self.free_blocks.append((start, end))

        # Merge adjacent free blocks
        self.free_blocks.sort()
        merged_free_blocks = []
        prev_start, prev_length = self.free_blocks[0]

        for current_start, current_length in self.free_blocks[1:]:
            if prev_start + prev_length == current_start:
                prev_length += current_length
            else:
                merged_free_blocks.append((prev_start, prev_length))
                prev_start, prev_length = current_start, current_length

        merged_free_blocks.append((prev_start, prev_length))
        self.free_blocks = merged_free_blocks


class Person:
    def __init__(self):
        self.status = 0


allocator = MemoryAllocator(1024)

# Allocate memory for a new person
person_memory = allocator.allocate(Person().__sizeof__())
person_instance = Person.__new__(Person)
person_instance.memory_view = person_memory

print(person_instance.status)  # Output should be 0, as status is initialized to 0.