import os

filename = "example.txt"
command = "ls {}".format(filename)
os.system(command)