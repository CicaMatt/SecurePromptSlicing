import sys

def scan(format_string):
    buffer_size = 1024
    input_stream = sys.stdin.read(buffer_size)
    
    if format_string == "%s\n":
        newline_index = input_stream.find('\n')
        if newline_index != -1:
            result = input_stream[:newline_index]
            return len(result) + 1, result
        else:
            return len(input_stream), input_stream
    
    return 0, ""

# Example usage:
if __name__ == "__main__":
    count, string = scan("%s\n")
    print(f"Characters read: {count}")
    print(f"String: '{string}'")