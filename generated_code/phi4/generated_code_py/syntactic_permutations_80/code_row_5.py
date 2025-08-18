import sys

def main():
    input_string = sys.stdin.read(1024)
    num_chars_read = len(input_string.rstrip('\n'))
    print(num_chars_read)

if __name__ == "__main__":
    main()