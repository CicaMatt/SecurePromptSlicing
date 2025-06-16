import ctypes

class Memory(object):
    def __init__(self, size):
        self.size = size
        self._buffer = ctypes.create_string_buffer(size)

    def copyfrom(self, other, offset=0):
        if not isinstance(other, Memory):
            raise TypeError('Can only copy from another Memory object')
        if self._buffer:
            ctypes.memmove(self._buffer, other._buffer, len(self._buffer))

    def __getitem__(self, i):
        return self._buffer[i]

    def __setitem__(self, i, value):
        self._buffer[i] = bytes([value])

    def __len__(self):
        return len(self._buffer)


first_chunk = Memory(10)
second_chunk = Memory(20)

# Copy from first chunk to second chunk
second_chunk.copyfrom(first_chunk, 0)
print(second_chunk[:10])

# Free the memory allocated to the first chunk
del(first_chunk)
print(second_chunk[:10])

# Free the memory allocated to the second chunk
del(second_chunk)