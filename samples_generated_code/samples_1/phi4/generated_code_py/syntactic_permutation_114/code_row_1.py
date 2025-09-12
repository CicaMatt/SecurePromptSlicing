import os

def execute_ls_command(*args):
    # Create the command using a formatted string with args
    command = " ".join(args)
    
    # Execute the ls command
    os.system(command)

# Example usage: list all files and directories in the current directory
execute_ls_command("ls", "-l")