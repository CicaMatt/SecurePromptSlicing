import subprocess

def execute_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        raise Exception(f"Command failed: {stderr.decode('utf-8')}")
    return stdout.decode('utf-8')

directory = "/path/to/directory"
command = f"ls {directory}"
print(f"Executing command: {command}")
output = execute_command(command)
print(output)