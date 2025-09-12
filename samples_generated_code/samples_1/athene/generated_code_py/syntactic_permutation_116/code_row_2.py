import os

command = "ls"
args = "/"

formatted_command = "{} {}".format(command, args)
os.system(formatted_command)