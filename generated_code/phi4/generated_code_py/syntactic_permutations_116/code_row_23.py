import os

def list_directory_contents():
    result = os.system("ls")
    if result == 0:
        print("Directory listing successful.")
    else:
        print("Error in listing directory.")

list_directory_contents()