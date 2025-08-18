import os

command = "ls"
args = "-l"

print_string = "{} {}".format(command, args)
os.system(print_string)