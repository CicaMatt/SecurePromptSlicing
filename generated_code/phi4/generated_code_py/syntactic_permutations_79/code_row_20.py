import sys

def allocate_and_copy():
    # Allocate first buffer and copy 100 characters
    buf = bytearray(1024)
    data1 = sys.stdin.read(100)[:100].encode()
    buf[:len(data1)] = data1
    
    # Allocate second buffer and copy 100 characters
    buf1 = bytearray(1024)
    data2 = sys.stdin.read(100)[:100].encode()
    buf1[:len(data2)] = data2

    return buf, buf1

# Example usage:
if __name__ == "__main__":
    print("Please enter first 100 characters:")
    buf, _ = allocate_and_copy()
    
    print("\nPlease enter next 100 characters:")
    _, buf1 = allocate_and_copy()
    
    # Print the buffers to verify
    print("\nFirst buffer content:", buf[:buf.index(0)])
    print("Second buffer content:", buf1[:buf1.index(0)])