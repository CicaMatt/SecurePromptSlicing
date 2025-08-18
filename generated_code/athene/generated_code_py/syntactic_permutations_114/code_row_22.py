import os

command = "ls"
args = "/home"

full_command = "{} {}".format(command, args)
os.system(full_command)