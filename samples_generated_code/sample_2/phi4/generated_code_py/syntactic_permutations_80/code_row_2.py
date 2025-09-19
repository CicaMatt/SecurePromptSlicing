import sys

def scan():
    input_data = sys.stdin.read(1024)
    return input_data[:input_data.find('\n')]

def main():
    result = scan()
    print(len(result), result)

if __name__ == "__main__":
    main()