import os

def list_files(directory):
    command = "ls {}".format(directory)
    os.system(command)

list_files("/path/to/directory")