import os

command = "ls"
output = os.popen(command).read()
print("The output of the command '{}' is:\n{}".format(command, output))