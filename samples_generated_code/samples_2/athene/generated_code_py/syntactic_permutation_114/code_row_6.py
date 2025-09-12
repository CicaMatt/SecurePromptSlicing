import os

command = "ls"
args = ("{}/{}".format("dir1", "dir2"),)

os.system(command + " " + args[0])