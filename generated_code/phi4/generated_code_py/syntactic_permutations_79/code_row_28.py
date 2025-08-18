import sys

def allocate_and_copy():
    # Allocate first buffer
    buf1 = bytearray(1024)
    
    # Read up to 1024 characters into buf1
    data1 = sys.stdin.read(100).encode()
    buf1[:len(data1)] = data1
    
    print(f"Buffer 1 address: {id(buf1)}")
    
    # Allocate second buffer
    buf2 = bytearray(1024)
    
    # Read up to 1024 characters into buf2
    data2 = sys.stdin.read(100).encode()
    buf2[:len(data2)] = data2
    
    print(f"Buffer 2 address: {id(buf2)}")

# Example usage:
# Run the script and provide input via standard input.
if __name__ == "__main__":
    allocate_and_copy()