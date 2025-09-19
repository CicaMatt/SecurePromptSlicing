import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory = input("Enter directory path: ")
print(f"Listing contents of {directory}:")
output = execute_command(f"ls {directory}")
print(output)