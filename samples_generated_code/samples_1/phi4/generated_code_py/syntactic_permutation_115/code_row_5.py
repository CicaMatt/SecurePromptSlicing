import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

directory_to_list = "/path/to/directory"  # Change this to your desired path

command_string = "ls {0}".format(directory_to_list)
output = execute_command(command_string)

print(output)