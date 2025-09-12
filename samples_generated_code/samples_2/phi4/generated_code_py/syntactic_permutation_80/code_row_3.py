import sys

def scan():
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size - 1)
    newline_position = input_data.find('\n')
    
    if newline_position != -1:
        # Exclude the newline character itself from being stored in the buffer.
        result = input_data[:newline_position]
        chars_read = newline_position + 1
    else:
        result = input_data
        chars_read = len(input_data)
    
    return result, chars_read

def main():
    user_input, num_chars_read = scan()
    print(f"Input: {user_input}")
    print(f"Number of characters read (including newline): {num_chars_read}")

if __name__ == "__main__":
    main()