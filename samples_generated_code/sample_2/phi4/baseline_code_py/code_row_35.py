import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

dir_path = "/some/directory/path"  # Replace with your directory path
command_string = "ls {0}".format(dir_path)

print(execute_command(command_string))