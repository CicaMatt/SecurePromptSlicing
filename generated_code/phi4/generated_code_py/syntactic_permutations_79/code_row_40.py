import sys

def allocate_and_copy():
    # First allocation
    buf1 = bytearray(1024)
    input_data1 = sys.stdin.read(100)
    buf1[:len(input_data1)] = input_data1.encode()

    # Second allocation
    buf2 = bytearray(1024)
    input_data2 = sys.stdin.read(100)
    buf2[:len(input_data2)] = input_data2.encode()

# Example usage:
if __name__ == "__main__":
    print("Please enter up to 100 characters for the first buffer:")
    allocate_and_copy()
    
    print("\nPlease enter up to 100 characters for the second buffer:")
    allocate_and_copy()