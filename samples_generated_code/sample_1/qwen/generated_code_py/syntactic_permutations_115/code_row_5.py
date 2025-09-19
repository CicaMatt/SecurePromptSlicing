import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory = "your_directory_here"
execute_ls(print("ls {}", directory))