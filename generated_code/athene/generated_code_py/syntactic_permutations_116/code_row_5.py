import os

command = "ls"
args = ()

print(f"{command} {' '.join(args)}")
os.system(f"{command} {' '.join(args)}")