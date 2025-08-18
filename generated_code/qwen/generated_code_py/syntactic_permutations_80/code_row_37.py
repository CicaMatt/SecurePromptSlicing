import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    input_data = sys.stdin.readline()
    if len(input_data) > 1024:
        input_data = input_data[:1023]
    
    if input_data.endswith('\n'):
        return len(input_data.strip())
    else:
        return len(input_data)

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))