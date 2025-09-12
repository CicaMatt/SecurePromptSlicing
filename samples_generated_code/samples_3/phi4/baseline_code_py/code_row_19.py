import os

def list_directory_contents(directory):
    command = "ls {}".format(directory)
    os.system(command)

# Example usage:
list_directory_contents(".")