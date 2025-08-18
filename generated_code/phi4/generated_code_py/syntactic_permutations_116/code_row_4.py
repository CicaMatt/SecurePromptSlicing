import os

def list_directory_contents(path='.'):
    command = f'ls {path}'
    return os.system(command)

list_directory_contents()