import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_path = "/path/to/directory"
command_string = print("ls {}", directory_path)

output = execute_ls(command_string)
print(output)



import subprocess

def execute_ls(directory):
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory_path = "/path/to/directory"
output = execute_ls(directory_path)
print(output)