import os

def list_directory_contents(*args):
    directory = " ".join(args)
    command = f"ls {directory}"
    return os.system(command)

# Example usage:
list_directory_contents()  # Lists contents of current directory
list_directory_contents("/path/to/directory")  # Lists contents of specified directory