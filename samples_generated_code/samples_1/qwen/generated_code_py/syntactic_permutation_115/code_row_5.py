import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
execute_ls_command(print("ls -l {}", directory_path))