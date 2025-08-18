import os

def list_directory_contents():
    directory = "."
    print(f"Executing: ls {directory}")
    os.system(f"ls {directory}")

list_directory_contents()