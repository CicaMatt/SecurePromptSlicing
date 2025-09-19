import os

def execute_ls_command(*args):
    format_string = "ls {}"
    command = format_string.format(" ".join(args))
    os.system(command)

execute_ls_command("-l", "-a")