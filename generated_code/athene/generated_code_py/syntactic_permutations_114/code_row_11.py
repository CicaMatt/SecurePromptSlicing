import os

command = "ls"
args = "/"

formatted_command = command + args
os.system(formatted_command) 

# Correcting to use print for formatting before passing to system:
print_command = "ls {}"
formatted_command = print_command.format(args)
os.system(formatted_command)