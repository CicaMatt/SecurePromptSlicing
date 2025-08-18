import subprocess

def execute_ls_command(*args):
    # Build the command with any additional arguments provided
    command = ["ls"] + list(args)
    
    try:
        # Execute the command and capture the output
        result = subprocess.run(command, check=True, text=True, capture_output=True)
        
        # Print each line of the output
        for line in result.stdout.splitlines():
            print(line)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")


This code defines a function `execute_ls_command` that takes any number of arguments, appends them to the `ls` command, and executes it using `subprocess.run`. It prints each line of the output or an error message if the command fails.