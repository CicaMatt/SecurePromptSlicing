import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters or until newline, whichever comes first
    data1 = sys.stdin.read(100).encode('utf-8')
    buf[:len(data1)] = data1
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Read another up to 100 characters or until newline, whichever comes first
    data2 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data2)] = data2

# Example usage:
# When running this script in an environment where input can be provided,
# you would typically redirect input from a file or provide it interactively.
if __name__ == "__main__":
    allocate_and_copy()