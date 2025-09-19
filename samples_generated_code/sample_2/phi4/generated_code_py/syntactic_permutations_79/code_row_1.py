import sys

def main():
    # Allocate first buffer
    buf1 = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data1 = sys.stdin.read(100).encode('utf-8')
    buf1[:len(data1)] = data1
    
    # Allocate second buffer
    buf2 = bytearray(1024)
    
    # Read up to 100 characters into the second buffer
    data2 = sys.stdin.read(100).encode('utf-8')
    buf2[:len(data2)] = data2

if __name__ == "__main__":
    main()