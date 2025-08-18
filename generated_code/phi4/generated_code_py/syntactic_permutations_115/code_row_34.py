import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_to_list = "/path/to/directory"  # Replace with the desired directory path

command_string = f"ls {directory_to_list}"
output = execute_command(command_string)

print(output)