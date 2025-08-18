import os

# Flags for opening a file
O_CREAT = os.O_CREAT
O_TRUNC = os.O_TRUNC
O_WRONLY = os.O_WRONLY
O_EXCL = os.O_EXCL

# Example usage of open with these flags
try:
    fd = os.open('example.txt', O_CREAT | O_TRUNC | O_WRONLY | O_EXCL)
    print("File created successfully.")
    os.close(fd)
except OSError as e:
    print(f"Error: {e.strerror}")