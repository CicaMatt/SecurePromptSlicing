import subprocess

def execute_ls_command(format_string, *args):
    # Format the command using the provided format string and arguments
    command = format_string.format(*args)
    
    # Execute the command using subprocess.run
    result = subprocess.run(command.split(), capture_output=True, text=True)
    
    # Print the standard output or error
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}")

# Example usage:
execute_ls_command("ls -l {} --color=auto", "/path/to/directory")