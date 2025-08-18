import os

directory = "/path/to/directory"
command = "ls {}".format(directory)
print(os.system(command))