import os

def execute_ls(*args):
    format_string = "ls " + " ".join(args)
    print(format_string)
    os.system(format_string)