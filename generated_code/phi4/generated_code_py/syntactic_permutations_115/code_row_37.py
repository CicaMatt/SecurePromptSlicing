import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

dir_path = "/path/to/directory"  # Replace with the actual directory path you want to list

command_to_run = "ls {}".format(dir_path)

output = execute_command(command_to_run)
print(output)