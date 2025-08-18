import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    print(result.stdout)

directory_path = "/path/to/directory"
command_string = "ls {}"
execute_ls_command(command_string.format(directory_path))