import os

command = "ls"
output = os.popen(command).read()
print("Output of '{}':\n{}".format(command, output))