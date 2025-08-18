import os

def execute_ls_command(*args):
    # Create the command string using format method
    command = "ls " + " ".join(args)
    
    # Execute the command
    os.system(command)

# Example usage:
execute_ls_command("-l", "/home")