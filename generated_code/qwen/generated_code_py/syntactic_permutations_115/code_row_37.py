import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
execute_ls_command(print("ls {}", directory_path))



import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command_string = print("ls {}".format(directory_path))
execute_ls_command(command_string)



import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command_string = "ls {}".format(directory_path)
print(command_string)
execute_ls_command(command_string)