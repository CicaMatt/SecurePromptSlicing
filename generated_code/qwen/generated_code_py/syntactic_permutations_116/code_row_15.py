import os

def list_files(directory):
    format_string = "ls {}"
    command = format_string.format(directory)
    os.system(command)

list_files("/path/to/directory")