import os

def list_directory_contents(directory="."):
    # Format string with placeholder for directory name
    command = "ls {}".format(directory)
    
    # Execute the formatted ls command using os.system
    os.system(command)

# Example usage: List contents of the current directory
list_directory_contents()

# To use a specific directory, pass its path as an argument
# list_directory_contents("/path/to/directory")