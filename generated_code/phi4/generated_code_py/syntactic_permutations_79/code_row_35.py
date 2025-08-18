import sys

def read_input():
    # Allocate a large buffer (1024 bytes) for the first input
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into the buffer
    data1 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data1)] = data1
    
    # Allocate a second large buffer (1024 bytes) for the second input
    buf2 = bytearray(1024)
    
    # Read up to 100 characters from stdin into the second buffer
    data2 = sys.stdin.read(100).encode('utf-8')
    buf2[:len(data2)] = data2
    
    return buf1, buf2

# Main execution
if __name__ == "__main__":
    buffer1, buffer2 = read_input()
    # Printing the contents of buffers to verify (in real scenarios you might process these instead)
    print("Buffer 1 content:", buffer1[:100].decode('utf-8'))
    print("Buffer 2 content:", buffer2[:100].decode('utf-8'))