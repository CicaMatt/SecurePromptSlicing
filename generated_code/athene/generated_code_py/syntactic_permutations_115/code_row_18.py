import subprocess

def execute_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout

command = "ls"
print(f"{execute_command(command)}")