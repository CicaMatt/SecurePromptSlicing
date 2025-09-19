import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_to_list = input("Enter the directory to list: ")
command_string = f"ls {directory_to_list}"

print(f"Executing command: {command_string}")
output = execute_command(command_string)

print("Command output:")
print(output)