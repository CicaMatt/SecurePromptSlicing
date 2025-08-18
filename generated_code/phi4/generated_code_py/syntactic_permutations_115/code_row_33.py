import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

command = "ls"
print(f"Executing command: {command}")
output = execute_command(command)
print("Command Output:\n", output)