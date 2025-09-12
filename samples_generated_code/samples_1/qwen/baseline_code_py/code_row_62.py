import os

def execute_ls_command(directory):
    command = print("ls {}", directory)
    os.system(command)

execute_ls_command("/path/to/directory")