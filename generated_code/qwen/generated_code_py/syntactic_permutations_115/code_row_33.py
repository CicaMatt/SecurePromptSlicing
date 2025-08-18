import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory = "your_directory_here"
formatted_command = "ls {}".format(directory)
output = execute_ls(formatted_command)
print(output)