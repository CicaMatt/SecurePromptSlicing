import os

command = "ls"
args = "/home/user"

full_command = "{} {}".format(command, args)
os.system(full_command)