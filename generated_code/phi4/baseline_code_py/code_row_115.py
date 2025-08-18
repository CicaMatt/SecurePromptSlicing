import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

directory_to_list = "."

command_str = "ls {dir}"
formatted_command = command_str.format(dir=directory_to_list)

output = execute_command(formatted_command)
print(output)