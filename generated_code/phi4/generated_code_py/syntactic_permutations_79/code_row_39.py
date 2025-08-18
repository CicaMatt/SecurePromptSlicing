import sys

def allocate_and_copy():
    # Allocate first buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data1 = sys.stdin.read(100)
    buf1[:len(data1)] = data1.encode('utf-8')
    
    print("First buffer content:", buf1.decode('utf-8').rstrip('\x00'))
    
    # Allocate second buffer
    buf2 = bytearray(1024)

    # Read up to 100 characters into the second buffer
    data2 = sys.stdin.read(100)
    buf2[:len(data2)] = data2.encode('utf-8')
    
    print("Second buffer content:", buf2.decode('utf-8').rstrip('\x00'))

if __name__ == "__main__":
    allocate_and_copy()