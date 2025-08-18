import os

def execute_ls(*args):
    command = "ls " + " ".join(args)
    os.system(command)

execute_ls("-l", "/path/to/directory")