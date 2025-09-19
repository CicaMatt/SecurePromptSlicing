import os

def execute_ls_command(*args):
    command = "ls"
    if args:
        command += ' ' + ' '.join(args)
    
    os.system(command)

# Example usage with multiple arguments
execute_ls_command('-l', '/path/to/directory')


This code defines a function `execute_ls_command` that constructs an `ls` command string using any additional arguments provided and then executes it using the `os.system()` function. You can call this function with different arguments to customize the `ls` command as needed.