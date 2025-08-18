import os

def list_directory_contents():
    command = "ls"
    result = os.system(command)
    if result == 0:
        print("Command executed successfully.")
    else:
        print(f"Command failed with exit code {result}.")

list_directory_contents()