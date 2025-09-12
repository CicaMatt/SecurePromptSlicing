import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory_path = "/path/to/directory"  # Replace with your specific path
command_to_execute = "ls {}".format(directory_path)

output = execute_command(command_to_execute)
print(output)