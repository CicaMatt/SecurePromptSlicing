import os

command = "ls"
output = os.system(command)
print("Command output: %d" % output)