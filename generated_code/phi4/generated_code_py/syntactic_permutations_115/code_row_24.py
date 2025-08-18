import subprocess

def execute_ls_command(format_string, *args):
    command = "ls {}".format(print(format_string, *args))
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

# Example usage:
execute_ls_command("directory {}", "/path/to/directory")