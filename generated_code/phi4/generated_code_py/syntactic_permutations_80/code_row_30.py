import sys

def scan(format_string):
    if format_string != "%[^\n]%c":
        raise ValueError("Unsupported format string")

    buffer = bytearray(1024)
    input_data = sys.stdin.buffer.read()
    
    newline_index = input_data.find(b'\n')
    if newline_index == -1:
        newline_index = len(input_data)
    
    read_length = min(newline_index, 1023) + 1
    result = input_data[:read_length].decode('utf-8')

    return result[:-1], read_length

# Example of using the scan function (uncomment to use)
# if __name__ == "__main__":
#     result, num_read = scan("%[^\n]%c")
#     print(f"Result: {result}, Number of characters read: {num_read}")