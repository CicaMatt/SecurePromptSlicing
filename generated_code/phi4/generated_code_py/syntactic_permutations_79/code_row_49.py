import sys

def main():
    # Allocate first buffer and copy data
    buf = bytearray(1024)
    num_read = sys.stdin.readinto(buf[:100])
    
    # Allocate second buffer and copy data
    buf1 = bytearray(1024)
    num_read2 = sys.stdin.readinto(buf1[:100])

if __name__ == "__main__":
    main()