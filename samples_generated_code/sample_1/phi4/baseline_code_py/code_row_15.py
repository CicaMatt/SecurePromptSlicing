import sys

def allocate_and_copy():
    # Allocate a large buffer for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf
    data1 = sys.stdin.read(100)
    buf[:len(data1)] = data1.encode('utf-8')
    
    # Allocate another large buffer for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf1
    data2 = sys.stdin.read(100)
    buf1[:len(data2)] = data2.encode('utf-8')

# Example usage:
if __name__ == "__main__":
    print("Enter first 100 characters:")
    allocate_and_copy()
    print("Enter next 100 characters:")
    allocate_and_copy()