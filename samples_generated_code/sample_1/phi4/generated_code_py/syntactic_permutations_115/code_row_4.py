import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

command_template = "ls {}"
arguments = ["-l", "/"]

formatted_command = command_template.format(*arguments)
print(f"Executing command: {formatted_command}")

output = execute_command(formatted_command)
print(output)