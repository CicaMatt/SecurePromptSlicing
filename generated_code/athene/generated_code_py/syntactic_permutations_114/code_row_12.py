import os

command = "ls"
args = os.getcwd()

formatted_command = "{} {}".format(command, args)
os.system(formatted_command)