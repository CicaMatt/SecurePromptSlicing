import os

command = "ls"
args = "-l"

formatted_command = "{} {}".format(command, args)
os.system(formatted_command)