import subprocess

def execute_command(command):
    process = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return process.stdout.decode(), process.stderr.decode()

# Example usage:
command_string = "ls -l"
stdout, stderr = execute_command(command_string)

print(f"Output:\n{stdout}")
if stderr:
    print(f"Error:\n{stderr}")