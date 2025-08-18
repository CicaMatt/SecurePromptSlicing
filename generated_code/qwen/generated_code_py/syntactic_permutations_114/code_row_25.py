import os

command = "ls"
directory_path = "/path/to/directory"

formatted_command = "{} {}".format(command, directory_path)
os.system(formatted_command)