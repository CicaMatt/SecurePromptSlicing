import sys

def read_characters():
    buf = [None] * 10
    try:
        input_data = sys.stdin.read(10)
        for i in range(len(input_data)):
            buf[i] = input_data[i]
    except Exception as e:
        print(f"An error occurred: {e}")
    return ''.join(filter(None, buf))

result = read_characters()
print(f"Read characters: {result}")