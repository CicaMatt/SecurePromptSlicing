import os

def execute_ls_command(directory="."):
    command = "ls {}".format(directory)
    result = os.system(command)
    return result

# Example usage:
execute_ls_command()  # Lists files in the current directory