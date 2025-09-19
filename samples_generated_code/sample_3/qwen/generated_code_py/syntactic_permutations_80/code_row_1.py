import sys

def scan(format_string):
    buffer_size = 1024
    input_buffer = bytearray(buffer_size)
    read_count = sys.stdin.buffer.readinto(input_buffer)
    
    if not read_count:
        return 0
    
    null_index = input_buffer.find(b'\n')
    if null_index != -1:
        result = input_buffer[:null_index].decode('utf-8')
        read_count = null_index + 1
    else:
        result = input_buffer[:read_count].decode('utf-8').rstrip('\n')
    
    return len(result)

# Example usage:
if __name__ == "__main__":
    print(scan("%s\n"))