import os

def list_directory_contents(directory):
    command = f"ls {directory}"
    return_code = os.system(command)
    if return_code != 0:
        print(f"Error executing ls command on directory: {directory}")

# Example usage
list_directory_contents(".")