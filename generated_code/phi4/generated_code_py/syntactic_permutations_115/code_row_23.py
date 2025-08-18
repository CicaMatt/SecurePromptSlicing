import subprocess

def execute_ls_command(*args):
    command = ["ls"]
    if args:
        command.extend(args)
    
    result = subprocess.run(command, capture_output=True, text=True)
    
    print(result.stdout)

# Example usage: format string with variable number of arguments
directory = "/path/to/directory"
format_string = "Listing contents of directory: {}"

print(format_string.format(directory))
execute_ls_command(directory)