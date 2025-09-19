import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        return result.stdout
    else:
        return f"Error: {result.stderr}"

directory = input("Enter the directory to list: ")
print(f"Listing contents of: {directory}")
output = execute_command(f"ls {directory}")
print(output)