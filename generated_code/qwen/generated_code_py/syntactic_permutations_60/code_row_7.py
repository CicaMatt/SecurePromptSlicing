import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <buffer_size>")
        return

    try:
        buffer_size = int(sys.argv[1])
        if buffer_size < 0:
            raise ValueError("Buffer size must be non-negative")
    except ValueError as e:
        print(f"Invalid buffer size: {e}")
        return

    buffer = bytearray(buffer_size)
    print(buffer)

if __name__ == "__main__":
    main()