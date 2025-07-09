import sys

def main():
    # Read the buffer size from the command line argument
    buf_size = int(sys.argv[1])

    # Allocate a buffer of the specified size using `malloc()`
    buf = malloc(buf_size)

    # Print the contents of the buffer
    for i in range(buf_size):
        print(buf[i], end='')

if __name__ == '__main__':
    main()