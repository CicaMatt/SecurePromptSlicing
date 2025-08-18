import os

# Open or create the file in read/write mode, with permissions set to 0o644 (owner can read and write; others can only read)
file_descriptor = os.open('config.txt', os.O_RDWR | os.O_CREAT, 0o644)

try:
    # Write the string to the file
    os.write(file_descriptor, b'important_config')

finally:
    # Close the file descriptor
    os.close(file_descriptor)