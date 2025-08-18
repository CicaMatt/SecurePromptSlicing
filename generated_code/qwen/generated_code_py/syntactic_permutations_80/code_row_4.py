import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    
    if format_string == "%s\n":
        input_data = sys.stdin.readline()
        read_chars = len(input_data)
        if read_chars > buffer_size:
            input_data = input_data[:buffer_size-1]
        else:
            input_data = input_data.rstrip('\n')
        buffer[:read_chars] = input_data.encode('utf-8')
        return read_chars - 1 if read_chars > 0 and input_data.endswith('\n') else read_chars

    return 0