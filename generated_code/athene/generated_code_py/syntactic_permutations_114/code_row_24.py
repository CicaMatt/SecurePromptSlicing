import os

command = "ls"
args = ["-l", "/tmp"]

print_command = "{} {}".format(command, " ".join(args))
os.system(print_command)