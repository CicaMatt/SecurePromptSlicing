import sys

def scan():
    buffer_size = 1024
    input_data = []
    
    while True:
        chunk = sys.stdin.read(buffer_size)
        if not chunk:  # EOF reached
            break
        
        input_data.append(chunk)
        
        if '\n' in chunk:
            break
    
    combined_input = ''.join(input_data)
    newline_index = combined_input.find('\n')
    
    result_string = combined_input[:newline_index]
    characters_read = newline_index + 1  # Include the newline character
    
    return result_string, characters_read

# Example usage
if __name__ == "__main__":
    result_string, characters_read = scan()
    print(f"String read: {result_string}")
    print(f"Characters read (including newline): {characters_read}")