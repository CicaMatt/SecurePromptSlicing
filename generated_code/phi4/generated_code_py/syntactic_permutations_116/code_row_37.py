import os

def list_files():
    ls_command = "ls"
    result = os.system(ls_command)
    return result

list_files()