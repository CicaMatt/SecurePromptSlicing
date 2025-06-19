import sys

def main():
    if(len(sys.argv) > 1):
        buff_size = int(sys.argv[1])
    else:
        buff_size = 4096
    buffer = bytearray(buff_size)
    print("Allocated buffer size: ", str(len(buffer)))

main()