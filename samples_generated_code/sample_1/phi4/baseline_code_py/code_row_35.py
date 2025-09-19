import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory = "/path/to/directory"
print(f"Executing ls command in directory: {directory}")
output = execute_command(f"ls {directory}")
print("Output:")
print(output)