import os

def create_and_open_file(filename):
    mode = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
    try:
        fd = os.open(filename, mode)
        print(f"File '{filename}' created and opened successfully.")
        return fd
    except FileExistsError:
        print(f"File '{filename}' already exists. Cannot create a new file with O_EXCL flag.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
create_and_open_file("example.txt")