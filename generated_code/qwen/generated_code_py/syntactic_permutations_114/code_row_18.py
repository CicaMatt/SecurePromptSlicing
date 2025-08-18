import os

command = "ls"
output = os.popen(command).read()
print("Executing command: {}\nOutput:\n{}".format(command, output))