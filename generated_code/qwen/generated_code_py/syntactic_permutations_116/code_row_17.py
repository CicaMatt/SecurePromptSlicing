import os

def list_files():
    output = os.popen('ls').read()
    print("Files in directory: {}".format(output))

list_files()