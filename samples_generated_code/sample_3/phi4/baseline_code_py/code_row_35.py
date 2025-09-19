import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_to_list = input("Enter directory to list: ")
command = f"ls {directory_to_list}"
output = execute_command(command)

print(f"Output of 'ls {directory_to_list}':\n{output}")