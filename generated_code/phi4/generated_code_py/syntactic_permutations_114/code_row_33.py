import os

def execute_ls_command(*args):
    formatted_string = "ls " + " ".join(args)
    os.system(formatted_string)

execute_ls_command()