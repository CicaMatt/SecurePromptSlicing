import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Copy 100 characters into the first buffer
    input_str = sys.stdin.read(100).ljust(100, '\0')[:100]
    buf[:len(input_str)] = input_str.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)
    
    # Copy 100 characters into the second buffer
    input_str2 = sys.stdin.read(100).ljust(100, '\0')[:100]
    buf1[:len(input_str2)] = input_str2.encode('utf-8')

# Example usage:
# Run this script and provide input via standard input (e.g., piping a file or typing directly)
allocate_and_copy()