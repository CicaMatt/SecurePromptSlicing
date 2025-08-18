import os

def execute_ls_command(directory="."):
    command = f"ls {directory}"
    os.system(command)

# Example usage
execute_ls_command()