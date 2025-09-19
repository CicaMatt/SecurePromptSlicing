import sys

def scan():
    input_data = sys.stdin.read(1023)
    if len(input_data) >= 1023 and '\n' not in input_data:
        # If no newline was found, we read extra to ensure newline is included
        additional_chars = sys.stdin.read(1)
        return len(input_data) + 1, input_data + additional_chars
    elif '\n' in input_data:
        newline_index = input_data.index('\n')
        # Exclude the newline character from the returned data
        return newline_index + 1, input_data[:newline_index]
    
# Example usage (uncomment to use):
# num_read, content = scan()
# print(f"Number of characters read: {num_read}")
# print("Content:", content)