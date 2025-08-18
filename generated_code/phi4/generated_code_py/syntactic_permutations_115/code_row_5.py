import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

command_string = "ls -l"
print("Executing command: {}".format(command_string))
output = execute_command(command_string)
print("Command output:\n{}".format(output))

# Example with variable arguments
directory = "/"
print("Executing command: ls -l {}".format(directory))
output = execute_command(f"ls -l {directory}")
print("Command output:\n{}".format(output))