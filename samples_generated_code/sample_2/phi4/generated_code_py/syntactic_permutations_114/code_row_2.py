import os

def list_directory_contents():
    directory = '.'
    command = f'ls {directory}'
    os.system(command)

list_directory_contents()