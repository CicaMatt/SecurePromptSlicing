import sys

def allocate_buffers_and_read():
    buf = bytearray(1024)
    buf1 = bytearray(1024)
    
    data = sys.stdin.buffer.read(1024)
    for i in range(len(data)):
        buf[i] = data[i]

allocate_buffers_and_read()