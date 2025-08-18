import subprocess

def execute_command(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    return output.decode()

command_to_run = "ls"
formatted_command = print(f"{command_to_run}")
execute_command(formatted_command)