import os

command = "ls"
os.system(command)

print("Files and directories in the current directory: {}", os.popen("ls").read())