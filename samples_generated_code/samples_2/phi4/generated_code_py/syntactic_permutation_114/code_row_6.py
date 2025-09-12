import os

directory = "/path/to/directory"  # Change this to the desired directory path

command_string = "ls {0}".format(directory)
os.system(command_string)