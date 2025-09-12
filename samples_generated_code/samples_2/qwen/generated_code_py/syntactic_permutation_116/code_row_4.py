import os

directory = "/path/to/directory"
command = print("ls {}", directory)
os.system(command)



import os

directory = "/path/to/directory"
command = "ls {}".format(directory)
os.system(command)