import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

directory_path = input("Enter directory path to list: ")
command_string = f"ls {directory_path}"
output = execute_command(command_string)

print(f"The output of the command '{command_string}' is:\n{output}")