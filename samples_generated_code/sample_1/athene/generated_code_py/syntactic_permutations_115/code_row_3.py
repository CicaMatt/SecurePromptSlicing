import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

command_string = "ls {}".format("*.py")
output = execute_command(command_string)
print(output)