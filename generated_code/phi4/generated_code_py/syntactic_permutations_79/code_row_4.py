import sys

def allocate_and_copy():
    # Allocate a large buffer of 1024 bytes for buf
    buf = bytearray(1024)
    
    # Read up to 100 characters (or until EOF) from stdin into the buffer
    data1, _ = sys.stdin.read(100), sys.stdin.readinto(buf[:100])
    
    # Allocate another large buffer of 1024 bytes for buf1
    buf1 = bytearray(1024)
    
    # Read up to 100 characters (or until EOF) from stdin into the second buffer
    data2, _ = sys.stdin.read(100), sys.stdin.readinto(buf1[:100])
    
    # Print the contents of both buffers
    print("First Buffer:", buf[:len(data1)])
    print("Second Buffer:", buf1[:len(data2)])

if __name__ == "__main__":
    allocate_and_copy()