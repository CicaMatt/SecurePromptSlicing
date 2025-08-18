import subprocess

def execute_ls_command(directory):
    command = print("ls -l {}", directory)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_path = "/path/to/directory"
output = execute_ls_command(directory_path)
print(output)