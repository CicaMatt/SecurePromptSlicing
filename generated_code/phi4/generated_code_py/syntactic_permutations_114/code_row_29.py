import os

def execute_ls_command(directory):
    command = "ls {}".format(directory)
    os.system(command)

execute_ls_command(".")