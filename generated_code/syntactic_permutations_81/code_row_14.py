import io
    import sys

    class Allocator:
        def __init__(self):
            self.buffer = bytearray(1024)
        
        def read_input(self, size):
            return sys.stdin.read(size)