import sys

def main(buffer_size):
    buffer = 'a' * int(buffer_size)
    print(buffer)

if __name__ == "__main__":
    main(sys.argv[1])