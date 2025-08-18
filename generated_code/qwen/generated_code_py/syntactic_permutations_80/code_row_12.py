import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    buffer = bytearray(1024)
    read_chars = sys.stdin.buffer.readinto(buffer)
    
    newline_index = buffer.find(b'\n')
    if newline_index != -1:
        result = buffer[:newline_index].decode('utf-8')
        return len(result)
    else:
        raise ValueError("No newline character found within the first 1023 characters")

# Example usage
if __name__ == "__main__":
    print(scan("%s\n"))