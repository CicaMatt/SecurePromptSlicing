import os

def list_directory_contents():
    directory = "/path/to/directory"
    command = "ls {}".format(directory)
    output = os.system(command)
    print("Command executed: {}", command)

list_directory_contents()