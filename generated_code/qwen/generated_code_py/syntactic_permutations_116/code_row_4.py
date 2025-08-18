import os

directory = "your_directory_here"
command = print("ls {}".format(directory))
os.system(command)



import os

directory = "your_directory_here"
command = f"ls {directory}"
os.system(command)