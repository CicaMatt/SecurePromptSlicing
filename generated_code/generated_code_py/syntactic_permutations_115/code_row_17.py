import os
def ls(dirname):
    return os.listdir(dirname)
print("ls output is {}".format(ls('/')))