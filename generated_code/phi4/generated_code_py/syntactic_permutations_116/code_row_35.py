import os

def list_directory_contents():
    # Use os.popen to execute 'ls' command and capture its output
    result = os.popen('ls').read()
    print(result)

list_directory_contents()