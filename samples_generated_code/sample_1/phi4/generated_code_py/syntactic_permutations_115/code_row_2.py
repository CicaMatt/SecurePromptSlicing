import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode != 0:
        raise Exception(f"Command failed with error: {result.stderr}")
    return result.stdout.strip()

directory = input("Enter the directory to list: ")
command = f"ls {directory}"
print(f"Executing command: {command}")
try:
    output = execute_command(command)
    print(output)
except Exception as e:
    print(e)