import os
def execute_ls(directory):
    return os.system("ls {}".format(directory))

execute_ls("/etc")