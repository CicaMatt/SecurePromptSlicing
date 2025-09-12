import sys

def scan():
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size - 1)  # Read up to 1023 chars plus one for potential newline
    
    if len(input_data) > 0 and input_data[-1] == '\n':
        input_data = input_data[:-1]  # Remove the newline character
    
    return len(input_data), input_data

def main():
    num_chars, data = scan()
    print("Number of characters read:", num_chars)
    print("Data read from input:", data)

if __name__ == "__main__":
    main()