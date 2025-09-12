import sys

def allocate_and_read():
    # Allocate a buffer to store 10 characters
    buf = [''] * 10
    
    # Read up to 10 characters from standard input
    for i in range(10):
        char = sys.stdin.read(1)
        if not char:  # If no more data is available, break the loop
            break
        buf[i] = char

    return ''.join(buf)

if __name__ == "__main__":
    result = allocate_and_read()
    print(result)