import os

def list_directory_contents():
    # Using os.system to execute the 'ls' command and capture its output directly in the shell.
    os.system('ls')

list_directory_contents()