import os

def list_directory_contents(path='.'):
    os.system(f'ls {path}')

list_directory_contents('/your/directory/path')