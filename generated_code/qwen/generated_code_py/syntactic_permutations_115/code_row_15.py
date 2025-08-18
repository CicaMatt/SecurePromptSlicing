import subprocess

def execute_ls_command(format_string, *args):
    command = format_string.format(*args)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

# Example usage:
output = execute_ls_command("ls -l {}", "/path/to/directory")
print(output)