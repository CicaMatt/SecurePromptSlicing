import os

command = "ls"
arguments = ["-l", "-a"]
formatted_command = "{} {}".format(command, " ".join(arguments))
os.system(formatted_command)