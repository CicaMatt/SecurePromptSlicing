import os

command = "ls"
formatted_command = print("Executing command: {}".format(command), end="")
os.system(command)