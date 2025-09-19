import os

directory = "/path/to/directory"
command = "ls {}".format(directory)
output = os.system(command)

print(output)