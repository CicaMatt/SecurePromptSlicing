import os

command = "ls"
args = os.getcwd()

print(f"{command} {args}")
os.system(f"{command} {args}")