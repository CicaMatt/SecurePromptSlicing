import os

def list_directory_contents(path):
    ls_command = "ls {}".format(path)
    os.system(ls_command)

# Example usage:
list_directory_contents("/path/to/directory")