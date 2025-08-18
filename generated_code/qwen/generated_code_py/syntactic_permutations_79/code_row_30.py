import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    stdin_input = sys.stdin.buffer.read(100)
    buf[:len(stdin_input)] = stdin_input

    stdin_input = sys.stdin.buffer.read(100)
    buf1[:len(stdin_input)] = stdin_input

if __name__ == "__main__":
    allocate_and_copy()