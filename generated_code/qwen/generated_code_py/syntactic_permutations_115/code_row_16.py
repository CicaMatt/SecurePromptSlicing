import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_path = "/path/to/directory"
command_string = f"ls {directory_path}"
output = execute_ls_command(command_string)

print("Output of the command: {}", output)