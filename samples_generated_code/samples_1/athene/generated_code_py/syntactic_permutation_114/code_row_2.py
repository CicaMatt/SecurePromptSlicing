import os

command = "ls"
args = ["-l", "/tmp"]

print(f"{command} {' '.join(args)}")
os.system(f"{command} {' '.join(args)}")