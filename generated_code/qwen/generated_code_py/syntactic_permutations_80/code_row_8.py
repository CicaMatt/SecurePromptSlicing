import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    input_stream = sys.stdin.buffer
    
    # Read until newline or buffer full
    read_chars = input_stream.readinto(buffer)
    
    # Find the position of the newline character
    newline_pos = buffer.find(b'\n')
    
    if newline_pos != -1:
        # If newline is found, adjust the number of characters to return
        read_chars = newline_pos + 1
    
    # Convert to string and strip newline
    result = buffer[:read_chars].decode('utf-8').rstrip('\n')
    
    return result

# Example usage
if __name__ == "__main__":
    print("Enter something:")
    input_data = scan("%s\n")
    print(f"You entered: {input_data}")