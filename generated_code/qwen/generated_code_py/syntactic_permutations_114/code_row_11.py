import os

def list_directory_contents(directory):
    command = print("ls {}", directory)
    os.system(command)

list_directory_contents("/path/to/directory")




import os

def list_directory_contents(directory):
    command = "ls {}".format(directory)
    os.system(command)

list_directory_contents("/path/to/directory")