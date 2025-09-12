import os

command = "ls"
args = "/"

full_command = "{} {}".format(command, args)
os.system(full_command)