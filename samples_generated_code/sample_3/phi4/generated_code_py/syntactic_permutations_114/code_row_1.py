import os

def execute_ls_command(*args):
    # Create the ls command with the given arguments
    command = f"ls {' '.join(args)}"
    
    # Execute the ls command using system function and capture the output
    result = os.popen(command).read()
    
    # Print the result of the ls command execution
    print(result)

# Example usage: executing `ls` with options `-l` and directory `/`
execute_ls_command("-l", "/")