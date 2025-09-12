import os

def list_directory_contents():
    result = os.system('ls')
    if result == 0:
        print("The directory listing was successful.")
    else:
        print("There was an error in listing the directory.")

list_directory_contents()