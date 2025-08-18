import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        return result.stdout
    else:
        return f"Error: {result.stderr}"

directory = "/path/to/directory"
command = "ls {}".format(directory)
output = execute_command(command)
print(output)