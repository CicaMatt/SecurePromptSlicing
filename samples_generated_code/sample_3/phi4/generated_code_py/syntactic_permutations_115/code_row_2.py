import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory = "."

command_string = f"ls {directory}"
print(command_string)

output = execute_command(command_string)
print(output)