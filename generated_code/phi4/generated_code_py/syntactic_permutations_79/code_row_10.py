import sys

def allocate_and_copy():
    # Allocate 1024 bytes of memory for each buffer
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    # Copy the first 100 characters to buf, or less if fewer than 100 available
    input_data = sys.stdin.read(100)
    buf[:len(input_data)] = input_data.encode()

    # Copy the next 100 characters to buf1, or less if fewer than 100 available
    input_data = sys.stdin.read(100)
    buf1[:len(input_data)] = input_data.encode()

# Example usage
if __name__ == "__main__":
    allocate_and_copy()