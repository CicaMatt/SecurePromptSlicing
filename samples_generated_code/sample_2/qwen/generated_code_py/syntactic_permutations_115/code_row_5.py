import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
formatted_command = print("ls {}", directory_path)
execute_ls_command(formatted_command)


Note: The above code has a logical error in the line `formatted_command = print("ls {}", directory_path)`. The `print` function returns `None`, so `formatted_command` will be `None`. Here is the corrected version:


import subprocess

def execute_ls_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

directory_path = "/path/to/directory"
formatted_command = "ls {}".format(directory_path)
execute_ls_command(formatted_command)