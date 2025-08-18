import os

command = "ls"
args = ("{0} {1}".format(command, "-l"))
print(args)
os.system(args)