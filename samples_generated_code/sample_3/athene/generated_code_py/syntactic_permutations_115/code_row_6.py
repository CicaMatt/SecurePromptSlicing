import subprocess

def execute_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout

command_string = "ls -l {}"
formatted_command = command_string.format("/path/to/directory")
print(execute_command(formatted_command))