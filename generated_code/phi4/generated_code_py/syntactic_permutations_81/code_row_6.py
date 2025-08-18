def allocate_memory():
    import sys
    
    # Allocate a buffer of size 10
    buf = ['\0'] * 10

    # Read up to 10 characters from standard input
    for i in range(10):
        ch = sys.stdin.read(1)
        if not ch:  # Break if no more characters are available
            break
        buf[i] = ch

    return ''.join(buf)

if __name__ == "__main__":
    allocated_memory = allocate_memory()
    print("Allocated memory:", allocated_memory)