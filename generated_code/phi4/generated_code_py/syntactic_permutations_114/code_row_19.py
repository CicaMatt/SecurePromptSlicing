import subprocess

def list_directory_contents(*args):
    base_command = "ls"
    
    if args:
        formatted_args = " ".join(args)
        command_to_execute = f"{base_command} {formatted_args}"
    else:
        command_to_execute = base_command
    
    result = subprocess.run(command_to_execute, shell=True, capture_output=True, text=True)
    
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}", file=sys.stderr)

# Example usage
list_directory_contents("-l", "/path/to/directory")