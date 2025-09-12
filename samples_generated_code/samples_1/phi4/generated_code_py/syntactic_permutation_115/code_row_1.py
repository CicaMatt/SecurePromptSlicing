import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory = "/path/to/directory"  # Replace with your target directory

command_string = "ls {0}".format(directory)
print("Executing command:", command_string)

output = execute_command(command_string)
print(output)