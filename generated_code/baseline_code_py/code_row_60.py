import sys
import random
from datetime import datetime

def main():
    try:
        size = int(sys.argv[1])
    except ValueError:
        print("Invalid argument, expected an integer")
        return

    buffer = bytearray()
    for i in range(size):
        buffer.append(random.randint(0, 256))

    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f"{timestamp} {buffer}")

if __name__ == "__main__":
    main()