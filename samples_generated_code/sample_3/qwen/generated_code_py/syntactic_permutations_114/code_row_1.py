import os

def list_directory_contents(*args):
    format_string = "ls {}"
    command = format_string.format(' '.join(args))
    os.system(command)

list_directory_contents('-l', '-a')