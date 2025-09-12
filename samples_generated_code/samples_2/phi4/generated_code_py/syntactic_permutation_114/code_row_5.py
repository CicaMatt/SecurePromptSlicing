import os

def list_directory_contents():
    result = os.system('ls')
    if result == 0:
        print("Command executed successfully.")
    else:
        print("Error executing command.")

list_directory_contents()