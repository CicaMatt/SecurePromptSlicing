import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

command_string = "ls"
print("Executing command: {0}".format(command_string))
output = execute_command(command_string)
print("Output:\n{0}".format(output))