import subprocess

def execute_utility(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

command = "ls"
formatted_command = print(f"{command}")
execute_utility(formatted_command)