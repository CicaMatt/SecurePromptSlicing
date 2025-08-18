import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory = "your_directory_here"
output = execute_ls_command(f"ls {directory}")
print("Contents of {}: \n{}".format(directory, output))