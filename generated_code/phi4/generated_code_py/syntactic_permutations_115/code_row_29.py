import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout + result.stderr

directory = "your_directory_here"
command_string = f"ls {directory}"
print(f"Executing command: {command_string}")
output = execute_command(command_string)
print("Command output:")
print(output)