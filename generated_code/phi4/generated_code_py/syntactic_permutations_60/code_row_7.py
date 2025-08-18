import ctypes

def main(buffer_size):
    # Allocate the buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Print the contents of the buffer
    print("Buffer content:", bytes(buffer))

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
    else:
        try:
            buffer_size = int(sys.argv[1])
            main(buffer_size)
        except ValueError:
            print("Please provide a valid integer for the buffer size.")