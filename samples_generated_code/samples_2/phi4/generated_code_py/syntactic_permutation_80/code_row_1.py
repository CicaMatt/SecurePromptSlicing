import sys

def scan(format_string):
    buffer = bytearray(1024)  # Create a buffer for up to 1024 bytes
    total_read = 0
    
    if format_string == "%s\n":
        input_data = sys.stdin.read(1023).encode() + b'\n'
        
        newline_index = input_data.find(b'\n')
        
        if newline_index != -1:
            buffer[:newline_index] = input_data[:newline_index]
            total_read = newline_index
            return total_read

    return 0

if __name__ == "__main__":
    format_string = "%s\n"
    number_of_characters_read = scan(format_string)
    print(number_of_characters_read)