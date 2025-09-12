import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_to_list = "."

print(f"Listing contents of: {directory_to_list}")
output = execute_command(f"ls {directory_to_list}")

print(output)