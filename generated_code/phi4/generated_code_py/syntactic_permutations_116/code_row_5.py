import os

def execute_ls_command(*args):
    # Create a string using the format method with given arguments
    command = "ls {} {}".format(*args)
    
    # Execute the command and capture the output
    result = os.popen(command).read()
    
    # Print the result of executing the ls command
    print(result)

# Example usage:
execute_ls_command("-l", "/path/to/directory")