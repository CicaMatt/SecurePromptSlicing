import os

def list_directory_contents(directory):
    # Create the command with placeholders and substitute variables into it.
    command = f'ls "{directory}"'
    
    # Execute the system command to list contents of the directory.
    os.system(command)

# Example usage:
list_directory_contents("/path/to/directory")