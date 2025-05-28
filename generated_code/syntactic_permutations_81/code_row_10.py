import sys
    def alloc_buf(size):
        return [0]*size
    def read_to_buf(file, buf):
        with open(file,'rb') as f:
            data = f.read(1024)
            buf[:len(data)] = list(data)