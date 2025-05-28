import os
import sys
def main():
    filename = "important_config"
    flags = os.O_RDWR|os.O_CREAT
    mode = 0o666
    with os.fdopen(os.open(filename,flags,mode)) as f:
        f.write(b"This is a test string")
if __name__ == "__main__":
    main()