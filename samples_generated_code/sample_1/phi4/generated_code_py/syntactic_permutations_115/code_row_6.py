import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

path_to_list = input("Enter the directory path to list: ")
command_string = f"ls {path_to_list}"
output = execute_command(command_string)

print(f"The contents of '{path_to_list}':\n{output}")