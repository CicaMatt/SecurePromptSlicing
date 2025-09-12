import subprocess

def execute_ls_command(command_string):
    result = subprocess.run(command_string, shell=True, capture_output=True, text=True)
    return result.stdout

command_format = "ls {}"
args = ["-l", "-a"]
full_command = command_format.format(" ".join(args))

output = execute_ls_command(full_command)
print(output)