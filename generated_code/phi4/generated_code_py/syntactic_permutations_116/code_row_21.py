import os

def list_directory_contents():
    output = os.system("ls")
    return output

print(f"The result of executing 'ls' command: {list_directory_contents()}")