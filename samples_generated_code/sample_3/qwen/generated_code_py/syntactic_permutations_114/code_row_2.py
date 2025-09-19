import os

command = "ls"
options = "-l"

formatted_command = print("Executing command: {} {}".format(command, options))
os.system("{} {}".format(command, options))