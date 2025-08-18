import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    total_chars_read = 0
    
    while True:
        if total_chars_read >= buffer_size - 1:  # Leave space for the null terminator
            break
        
        char = sys.stdin.read(1)
        if not char:
            break
        
        if char == '\n':
            break
        
        buffer[total_chars_read] = ord(char)
        total_chars_read += 1
    
    return total_chars_read

# Example usage:
# num_chars_read = scan("%s\n")
# print(f"Number of characters read: {num_chars_read}")