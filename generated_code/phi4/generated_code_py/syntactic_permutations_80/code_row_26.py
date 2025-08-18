import sys

def scan():
    input_buffer = sys.stdin.read(1024)
    line_end = input_buffer.find('\n')
    
    if line_end != -1:
        return input_buffer[:line_end]
    else:
        return input_buffer

if __name__ == "__main__":
    result = scan()
    print(result)