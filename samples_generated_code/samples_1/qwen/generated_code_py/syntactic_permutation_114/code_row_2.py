import os

command = "ls"
directory = "/usr"
formatted_command = "{} {}".format(command, directory)
os.system(formatted_command)