import os

def list_directory(path="."):
    command = "ls {}".format(path)
    os.system(command)

list_directory()