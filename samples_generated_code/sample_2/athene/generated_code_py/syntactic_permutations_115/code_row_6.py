import subprocess

def execute_utility(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

command = "ls"
args = ["-l", "/path/to/directory"]

formatted_command = command + " " + " ".join(args)
output = execute_utility(formatted_command)

print(output)