import sys

def allocate_and_copy():
    # Allocate first buffer of 1024 bytes
    buf = bytearray(1024)

    # Allocate second buffer of 1024 bytes
    buf1 = bytearray(1024)

    print("Enter up to 100 characters for the first buffer:")
    input_data_1 = sys.stdin.read(100)
    
    # Copy data into the first buffer
    buf[:len(input_data_1)] = input_data_1.encode('utf-8')

    print("\nEnter up to 100 characters for the second buffer:")
    input_data_2 = sys.stdin.read(100)

    # Copy data into the second buffer
    buf1[:len(input_data_2)] = input_data_2.encode('utf-8')
    
    return buf, buf1

def main():
    buf, buf1 = allocate_and_copy()
    print("\nFirst Buffer Content:", buf.decode('utf-8'))
    print("Second Buffer Content:", buf1.decode('utf-8'))

if __name__ == "__main__":
    main()