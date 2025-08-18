import sys

def scan():
    buffer = bytearray(1024)
    input_stream = sys.stdin.buffer.readinto(buffer)
    
    # Convert to string and find the position of newline character
    result_str = buffer[:input_stream].tobytes().decode('utf-8')
    newline_index = result_str.find('\n')

    if newline_index != -1:
        return result_str[:newline_index]
    else:
        return result_str

# Example usage (uncomment and run):
# if __name__ == "__main__":
#     user_input = scan()
#     print(user_input)