import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    buffer_size = 1024
    input_data = sys.stdin.read(buffer_size)
    
    newline_index = input_data.find('\n')
    if newline_index == -1:
        return len(input_data), input_data
    
    result_string = input_data[:newline_index]
    total_read = newline_index + 1
    
    return total_read, result_string

# Example usage
if __name__ == "__main__":
    read_count, string_result = scan("%s\n")
    print(f"Read {read_count} characters: '{string_result}'")