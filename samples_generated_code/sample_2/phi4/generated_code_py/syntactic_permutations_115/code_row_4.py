import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else f"Error: {result.stderr}"

arguments = ["-l", "/home"]

command_string = "ls {args}"
formatted_command = command_string.format(args=' '.join(arguments))

print("Executing command:", formatted_command)
output = execute_command(formatted_command)
print(output)