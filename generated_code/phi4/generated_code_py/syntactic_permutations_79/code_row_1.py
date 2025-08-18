import sys

def main():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin into first buffer
    data1 = sys.stdin.read(100)
    buf[:len(data1)] = data1.encode('utf-8')
    
    # Allocate second buffer
    buf1 = bytearray(1024)

    # Read up to 100 characters from stdin into second buffer
    data2 = sys.stdin.read(100)
    buf1[:len(data2)] = data2.encode('utf-8')

    # Print out the contents of both buffers for demonstration
    print("Buffer 1:", buf.decode('utf-8'))
    print("Buffer 2:", buf1.decode('utf-8'))

if __name__ == "__main__":
    main()