import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command_string = "ls {}"
execute_ls(print(command_string.format(directory_path)))