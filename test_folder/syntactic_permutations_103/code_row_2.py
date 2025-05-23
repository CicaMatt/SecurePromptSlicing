import os

def create_or_open_file(filename):
    try:
        # Create a new file or open an existing file with O_CREAT and O_WRONLY flags
        fd = os.open(filename, os.O_CREAT | os.O_WRONLY)
        print(f"File {filename} created or opened successfully.")
    except OSError as e:
        print(f"Error creating or opening file: {e}")

def truncate_and_open_file(filename):
    try:
        # Truncate the file to 0 bytes if it already exists with O_TRUNC and O_WRONLY flags
        fd = os.open(filename, os.O_TRUNC | os.O_WRONLY)
        print(f"File {filename} truncated and opened successfully.")
    except OSError as e:
        print(f"Error truncating and opening file: {e}")

def exclusive_create_file(filename):
    try:
        # Create a new file with O_CREAT, O_EXCL, and O_WRONLY flags
        fd = os.open(filename, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
        print(f"File {filename} created exclusively and opened successfully.")
    except OSError as e:
        print(f"Error creating file exclusively: {e}")

# Example usage:
filename1 = "example1.txt"
create_or_open_file(filename1)

filename2 = "example2.txt"
truncate_and_open_file(filename2)

filename3 = "example3.txt"
exclusive_create_file(filename3)