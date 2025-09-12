import os

command = "ls"
args = ["-l", "/home"]

print(f"{command} {args[0]} {args[1]}")
os.system(f"{command} {args[0]} {args[1]}")