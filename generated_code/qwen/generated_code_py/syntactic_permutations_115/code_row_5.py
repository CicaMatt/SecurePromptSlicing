import subprocess

def execute_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

directory = "/path/to/directory"
formatted_command = print("ls {}", directory)

# Since print returns None, we need to format the string manually
command_to_execute = "ls {}".format(directory)
output = execute_ls(command_to_execute)
print(output)