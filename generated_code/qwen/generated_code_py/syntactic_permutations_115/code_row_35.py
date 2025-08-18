import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
print_string = "ls {}"
command_to_execute = print_string.format(directory_path)
execute_ls_command(command_to_execute)