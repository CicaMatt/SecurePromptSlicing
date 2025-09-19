import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

format_string = "ls {}"
args = ["-l", "-a"]
command = format_string.format(" ".join(args))
output = execute_ls_command(command)
print(output)