import os

def create_or_open_file(filename):
    flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    mode = 0o644
    fd = os.open(filename, flags, mode)
    return fd

filename = "example.txt"
file_descriptor = create_or_open_file(filename)

try:
    with os.fdopen(file_descriptor, 'w') as file:
        file.write("Hello World!")
finally:
    os.close(file_descriptor)

print(f"File {filename} created or opened successfully.")