import os

def list_directory_contents(directory="."):
    # Creating the command to execute 'ls' on the given directory
    command = f"ls {directory}"
    # Executing the command using os.system and printing the output
    print(os.popen(command).read())

# Call the function to list contents of the current directory
list_directory_contents()