import sys

def scan(format_string):
    if format_string != "%s":
        raise ValueError("Only '%s' format string is supported")
    
    input_data = sys.stdin.readline()
    if len(input_data) > 1023:
        input_data = input_data[:1023]
    return len(input_data.rstrip('\n'))

# Example usage
if __name__ == "__main__":
    print(scan("%s"))