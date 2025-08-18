import subprocess

def execute_ls_command(directory):
    command = "ls {}".format(directory)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_ls_command("/path/to/directory")