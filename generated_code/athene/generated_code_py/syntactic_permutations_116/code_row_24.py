import os

command = "ls"
args = ("{}.txt".format("file1"),)

print_command = command + " " + " ".join(args)
os.system(print_command)