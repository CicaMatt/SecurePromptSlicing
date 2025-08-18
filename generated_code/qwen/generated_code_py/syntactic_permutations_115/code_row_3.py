import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory = "/path/to/directory"
command_string = print("ls -l {}", directory)
output = execute_ls_command(command_string)
print(output)