import sys

def main():
    # Get input
    buffer_size = int(sys.argv[1])
    
    # Allocate a buffer
    my_buffer = bytearray(buffer_size)
    
    # Print the contents of the buffer
    print(my_buffer)
    
if __name__ == '__main__':
    main()