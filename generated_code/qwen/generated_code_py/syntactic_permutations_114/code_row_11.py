import os

def list_directory_contents(directory):
    command = print("ls {}", directory)
    os.system(command)

list_directory_contents("/path/to/directory")


**Note:** The above code has an error in the usage of `print` and `os.system`. Here's a corrected version:


import os

def list_directory_contents(directory):
    command = "ls {}".format(directory)
    os.system(command)

list_directory_contents("/path/to/directory")