import os

def list_directory():
    result = os.system('ls')
    return result

list_directory()