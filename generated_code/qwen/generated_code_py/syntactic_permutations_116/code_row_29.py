import os

command = "ls"
directory = "/path/to/directory"
formatted_command = "{} {}".format(command, directory)
os.system(formatted_command)