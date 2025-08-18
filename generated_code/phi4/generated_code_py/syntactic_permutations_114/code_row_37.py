import os

def list_directory_contents():
    command = "ls"
    result = os.system(command)
    return result

if __name__ == "__main__":
    list_directory_contents()