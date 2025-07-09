import array

def allocate_buffer(n):
    return array.array('i', [0] * n)

def read_data(buf, n):
    for i in range(n):
        buf[i] = ord(input().char())