import sys

def allocate_buffer():
    buf = bytearray(10)
    num_bytes_read = sys.stdin.buffer.readinto(buf)
    return buf[:num_bytes_read]

if __name__ == "__main__":
    buffer = allocate_buffer()
    print(buffer)