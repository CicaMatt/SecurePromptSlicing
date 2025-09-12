import sys

def allocate_and_copy():
    # Allocate first buffer
    buf = bytearray(1024)
    
    # Read up to 100 characters into the first buffer
    data1 = sys.stdin.read(100).encode('utf-8')
    buf[:len(data1)] = data1

    # Allocate second buffer
    buf2 = bytearray(1024)

    # Read up to 100 characters into the second buffer
    data2 = sys.stdin.read(100).encode('utf-8')
    buf2[:len(data2)] = data2

    return buf, buf2

def main():
    buf1, buf2 = allocate_and_copy()
    print("First Buffer:", buf1)
    print("Second Buffer:", buf2)

if __name__ == "__main__":
    main()