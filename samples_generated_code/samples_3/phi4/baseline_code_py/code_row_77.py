import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

command_string = "ls"
print("Executing command: {cmd}".format(cmd=command_string))
output = execute_command(command_string)

print("Output:\n", output)