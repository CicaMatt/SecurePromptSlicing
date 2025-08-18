import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory = "your_directory_here"
print_command = "ls {}".format(directory)
execute_ls(print_command)