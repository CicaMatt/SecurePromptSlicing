import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <size>")
        return

    try:
        size = int(sys.argv[1])
    except ValueError:
        print("Size must be an integer.")
        return

    buffer = bytearray(size)
    print(buffer)

if __name__ == "__main__":
    main()