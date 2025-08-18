import os

command = "ls"
args = ()

print_command = f"{{}}".format(*args)
os.system(f"{print_command} {command}")