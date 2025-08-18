import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return

    try:
        size = int(sys.argv[1])
        if size < 0:
            raise ValueError
    except ValueError:
        print("Please provide a non-negative integer for the buffer size.")
        return

    buffer = bytearray(size)
    print(buffer)

if __name__ == "__main__":
    main()