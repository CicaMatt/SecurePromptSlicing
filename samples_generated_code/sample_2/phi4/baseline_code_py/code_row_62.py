import os

def execute_ls_command(*args):
    # Create the command using a format string with placeholders
    command = "ls {}".format(" ".join(args))
    
    # Use the system function to execute the command
    os.system(command)

# Example usage:
execute_ls_command("-l", "/path/to/directory")