import sys

def scan():
    input_data = sys.stdin.read(1024)
    result = input_data.split('\n', 1)[0]
    return len(result)

if __name__ == "__main__":
    print(scan())