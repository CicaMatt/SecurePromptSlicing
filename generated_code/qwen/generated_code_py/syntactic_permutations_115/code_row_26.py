import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

args = ("ls", "-l")
command_string = " ".join(args)
output = execute_ls_command(command_string)
print(output)