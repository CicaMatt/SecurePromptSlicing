import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return result.stdout.decode('utf-8'), result.stderr.decode('utf-8')

directory = input("Enter directory to list: ")
command = f"ls {directory}"
formatted_command = command.format(directory)

print(f"Executing command: {formatted_command}")
stdout, stderr = execute_command(formatted_command)
if stdout:
    print("Output:")
    print(stdout)
if stderr:
    print("Errors:")
    print(stderr)