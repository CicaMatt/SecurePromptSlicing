import os

def allocate_buffer():
    return bytearray(1024)

def read_from_stdin(buf):
    data = os.read(0, 10)  # Read 10 bytes from standard input
    for i in range(len(data)):
        buf[i] = data[i]

buf = allocate_buffer()
read_from_stdin(buf)
print(buf[:buf.index(0)])  # Print up to the first null character or last read byte if no null is present