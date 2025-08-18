import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

name = "World"
command_string = print("Hello, {}!".format(name), end="")
output = execute_command(command_string)
print(output)