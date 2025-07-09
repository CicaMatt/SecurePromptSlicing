import os

def run_cmd(args):
    return os.system(args)

print("Running ls command...")
run_cmd("ls -l")