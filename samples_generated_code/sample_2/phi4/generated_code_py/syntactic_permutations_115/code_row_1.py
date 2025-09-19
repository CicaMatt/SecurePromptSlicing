import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory = input("Enter directory path: ")
command_string = f"ls {directory}"

print(f"Executing command: {command_string}")
output = execute_command(command_string)
print(output)