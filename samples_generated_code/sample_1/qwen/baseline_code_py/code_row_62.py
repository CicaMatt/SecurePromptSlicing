import os

command = "ls"
directory = "/path/to/directory"
formatted_command = print("Executing command: {} {}".format(command, directory))
os.system("{} {}".format(command, directory))