import subprocess

command = "ls"
formatted_command = "{}"

result = subprocess.run(formatted_command.format(command), shell=True, capture_output=True)

print(result.stdout.decode())