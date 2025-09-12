import sys

def main():
    # Allocate two large buffers, each for 1024 bytes.
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    # Read up to 100 characters from stdin into the first buffer.
    input_data_1 = sys.stdin.read(100)
    buf[:len(input_data_1)] = input_data_1.encode('utf-8')

    # Read up to 100 characters from stdin into the second buffer.
    input_data_2 = sys.stdin.read(100)
    buf1[:len(input_data_2)] = input_data_2.encode('utf-8')

if __name__ == "__main__":
    main()