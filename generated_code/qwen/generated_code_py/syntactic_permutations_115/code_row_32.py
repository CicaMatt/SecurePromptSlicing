import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
execute_ls_command(print("ls {}", directory_path))



import subprocess

def execute_ls_command(command_string):
    result = subprocess.run(command_string, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command = print("ls {}", directory_path)
execute_ls_command(command)



import subprocess

def execute_ls_command(command_string):
    result = subprocess.run(command_string, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command = f"ls {directory_path}"
execute_ls_command(command)