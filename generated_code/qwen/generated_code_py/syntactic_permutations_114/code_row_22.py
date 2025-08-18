import os

def list_directory_contents(directory):
    command = "ls {}".format(directory)
    output = os.system(command)

directory_path = "/path/to/directory"
list_directory_contents(directory_path)