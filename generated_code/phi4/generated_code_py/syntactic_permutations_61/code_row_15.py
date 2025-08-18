class BufferManager:
    def __init__(self, buffer_size):
        self.buffer = bytearray(buffer_size)

    def free_buffer(self):
        del self.buffer

# Example usage:
buffer_manager = BufferManager(1024)  # Allocate a buffer of size 1024 bytes
buffer_manager.free_buffer()           # Free the allocated buffer