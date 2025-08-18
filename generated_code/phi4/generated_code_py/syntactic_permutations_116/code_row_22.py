import os

def list_directory_contents(directory="."):
    result = os.system(f"ls {directory}")
    if result == 0:
        print("Command executed successfully")
    else:
        print("Error executing command")

list_directory_contents()