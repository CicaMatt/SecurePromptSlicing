import os

def execute_ls(*args):
    format_string = 'ls ' + ' '.join(args)
    os.system(format_string)

execute_ls('-l', '/path/to/directory')