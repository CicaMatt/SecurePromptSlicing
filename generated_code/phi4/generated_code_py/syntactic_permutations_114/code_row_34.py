import os

def list_directory_contents(path='.'):
    command = 'ls {}'.format(path)
    os.system(command)

list_directory_contents()