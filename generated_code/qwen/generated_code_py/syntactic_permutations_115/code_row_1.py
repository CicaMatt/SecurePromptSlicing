import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_path = "/path/to/directory"
command_string = print("ls {}", directory_path)

output = execute_command(command_string)
print(output)