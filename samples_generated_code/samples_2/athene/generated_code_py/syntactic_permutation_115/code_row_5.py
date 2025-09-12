import subprocess

def execute_ls(directory):
    command = "ls {}".format(directory)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_ls("/path/to/directory")