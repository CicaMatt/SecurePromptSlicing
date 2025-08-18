import sys

def scan(format_string):
    input_buffer = []
    max_chars = 1023
    
    if format_string == "%s\n":
        while True:
            char = sys.stdin.read(1)
            if char == '':
                break
            if char != '\n':
                input_buffer.append(char)
                if len(input_buffer) >= max_chars:
                    break
            else:
                break
        
        return ''.join(input_buffer), len(''.join(input_buffer))
    else:
        raise ValueError("Unsupported format string")

if __name__ == "__main__":
    format_string = "%s\n"
    result, num_chars_read = scan(format_string)
    print(f"Read {num_chars_read} characters.")