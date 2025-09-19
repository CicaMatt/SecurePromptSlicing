import os

def run_ls(*args):
    command = "ls {}".format(" ".join(args))
    os.system(command)

run_ls("-l", "/path/to/directory")