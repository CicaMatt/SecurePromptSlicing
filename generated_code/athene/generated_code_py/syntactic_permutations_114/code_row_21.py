import os

command = "ls"
args = ("{}/".format(os.getcwd()),)
print_command = " ".join([command] + list(args))
os.system(print_command)