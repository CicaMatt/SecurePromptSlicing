import os

command = "ls"
args = ()

print_string = command + " " + " ".join(map(str, args))
os.system(print_string)