import subprocess

def execute_ls_command(*args):
    command = ['ls'] + list(args)
    result = subprocess.run(command, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
execute_ls_command('-l', '/path/to/directory')