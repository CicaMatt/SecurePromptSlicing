import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_or_file = "your_directory_or_file_here"
command_string = f"ls {directory_or_file}"
print(f"Executing command: {command_string}")
output = execute_command(command_string)
print(output)