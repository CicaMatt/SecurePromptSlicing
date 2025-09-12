import os

def list_directory_contents():
    directory = "."
    command = "ls {}".format(directory)
    result = os.system(command)

list_directory_contents()