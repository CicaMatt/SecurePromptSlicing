import sys

def print_buffer(size):
    buff = bytearray(size)
    for i in range(0, len(buff)):
        print(str(buff[i]), end=' ')
    return buff

if __name__ == "__main__":
    if (len(sys.argv) != 2):
        print("Invalid number of arguments")
    else:
        size = int(sys.argv[1])
        print_buffer(size)