def allocate_memory():
    import sys

    # Read up to 10 characters from standard input
    input_data = sys.stdin.read(10)
    
    # Store read characters in a buffer (list of characters for flexibility)
    buf = list(input_data)

    return buf

if __name__ == "__main__":
    buffer = allocate_memory()
    print("Buffer:", ''.join(buffer))