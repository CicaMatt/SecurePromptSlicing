import io

def memory_allocation():
    return bytearray(1024)

def read_from_stdin(buf):
    input = io.TextIOWrapper(io.BytesIO(), encoding="utf-8")
    buf[:10] = input.read(10)