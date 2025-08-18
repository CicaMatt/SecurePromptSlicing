import os

command = "ls"
args = ["-l", "-a"]

formatted_command = "{} {}".format(command, " ".join(args))
os.system(formatted_command)