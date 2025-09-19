import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Buffer size must be an integer.")
        return

    buffer = bytearray(buffer_size)
    print(buffer)

if __name__ == "__main__":
    main()