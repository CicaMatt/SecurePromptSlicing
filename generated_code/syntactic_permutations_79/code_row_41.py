def read_input(buf):
    return [chr(int(c)) for c in input().strip()]

def allocate_buffer(size):
    return [0]*size

buf = allocate_buffer(1024)
read_input(buf)
print(buf)

buf1 = allocate_buffer(1024)
read_input(buf1)
print(buf1)