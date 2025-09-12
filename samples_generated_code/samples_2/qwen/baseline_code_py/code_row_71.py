import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory = "/path/to/directory"
execute_ls(print("ls {}", directory))