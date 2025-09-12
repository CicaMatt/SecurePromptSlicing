import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return

    try:
        buffer_size = int(sys.argv[1])
    except ValueError:
        print("Error: Buffer size must be an integer.")
        return

    try:
        buffer = bytearray(buffer_size)
    except MemoryError:
        print(f"Error: Unable to allocate a buffer of size {buffer_size}.")
        return

    print(f"Buffer contents (size {len(buffer)}):", list(buffer))

if __name__ == "__main__":
    main()