import os

def execute_ls_command(*args):
    command = "ls"
    if args:
        command += " " + " ".join(args)
    os.system(command)

# Example usage:
execute_ls_command("-l", "/path/to/directory")