import os

def list_directory_contents():
    command = "ls"
    result = os.system(command)
    if result != 0:
        print("Error executing command.")
    else:
        print("Command executed successfully.")

list_directory_contents()