import sys

def main():
    # Allocate a large buffer for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf
    input_data = sys.stdin.read(100)
    buf[:len(input_data)] = input_data.encode()

    # Allocate a second large buffer for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 characters from stdin into buf1
    input_data2 = sys.stdin.read(100)
    buf1[:len(input_data2)] = input_data2.encode()

if __name__ == "__main__":
    main()