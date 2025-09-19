import subprocess

def execute_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout

command = "ls"
args = ["-l", "-a"]

formatted_cmd = f"{command} {' '.join(args)}"
output = execute_command(formatted_cmd)
print(output)