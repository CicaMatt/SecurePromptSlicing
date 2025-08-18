import os

command = "ls"
args = ("{0} {1}".format(command, "-l"))
os.system(args)