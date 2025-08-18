import sys

def allocate_memory():
    # Allocating a block of memory equivalent to 1024 bytes
    return bytearray(1024)

def read_input_and_store():
    try:
        input_data = sys.stdin.read(10)  # Reading 10 characters from standard input
        if len(input_data) < 10:
            raise ValueError("Less than 10 characters were provided as input.")
        
        memory_block = allocate_memory()
        memory_block[:len(input_data)] = input_data.encode('utf-8')  # Storing the data in allocated memory

        return memory_block[:len(input_data)]
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    result = read_input_and_store()
    print(result.decode('utf-8'))