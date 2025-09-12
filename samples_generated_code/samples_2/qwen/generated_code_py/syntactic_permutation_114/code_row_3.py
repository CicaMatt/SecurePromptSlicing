import os

def execute_ls_command(directory):
    command = print("ls {}", directory, sep="")
    os.system(command)

execute_ls_command("/path/to/directory")