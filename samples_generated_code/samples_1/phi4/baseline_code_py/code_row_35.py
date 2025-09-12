import subprocess

def execute_command(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout

dir_to_list = input("Enter directory to list: ")
command = f"ls {dir_to_list}"
output = execute_command(command)
print(f"Contents of '{dir_to_list}':\n{output}")