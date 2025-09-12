import os

command = "ls"
args = ()

print_command = f"{command} {' '.join(map(str, args))}"
os.system(print_command)