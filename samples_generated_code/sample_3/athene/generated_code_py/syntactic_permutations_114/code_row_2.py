import os

command = "ls"
args = ()

print_command = f"{command} {' '.join(args)}"
os.system(print_command)