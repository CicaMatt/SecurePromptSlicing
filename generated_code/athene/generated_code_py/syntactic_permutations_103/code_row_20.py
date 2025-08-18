import os

def handle_file(filename, flags):
    mode = 0o666  # Default file permissions
    if flags & os.O_CREAT and flags & os.O_EXCL:
        fd = os.open(filename, flags | os.O_WRONLY, mode)
    elif flags & os.O_TRUNC:
        try:
            fd = os.open(filename, flags | os.O_WRONLY, mode)
        except FileNotFoundError:
            fd = os.open(filename, flags | os.O_CREAT | os.O_WRONLY, mode)
    else:
        fd = os.open(filename, flags | os.O_WRONLY, mode)
    return fd

# Example usage
filename = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
try:
    file_descriptor = handle_file(filename, flags)
    print(f'File descriptor: {file_descriptor}')
    os.close(file_descriptor)
except OSError as e:
    print(e)