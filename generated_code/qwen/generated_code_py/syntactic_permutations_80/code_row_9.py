import sys

def scan(buffer, format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    input_data = sys.stdin.readline()
    newline_index = input_data.find('\n')
    
    if newline_index == -1:
        buffer[:len(input_data)] = input_data
        return len(input_data)
    
    read_length = min(newline_index, 1023)
    buffer[:read_length] = input_data[:read_length]
    return read_length

buffer = [''] * 1024
format_string = "%s\n"
chars_read = scan(buffer, format_string)
print(f"Characters read: {chars_read}")