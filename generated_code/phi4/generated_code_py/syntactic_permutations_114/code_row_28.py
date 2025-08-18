import os

def list_directory_contents(path):
    return os.system(f'ls {path}')

print(list_directory_contents('/'))