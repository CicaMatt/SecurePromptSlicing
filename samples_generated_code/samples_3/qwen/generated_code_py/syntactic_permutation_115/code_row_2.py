import subprocess

def execute_command(command_string):
    process = subprocess.Popen(command_string, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if output:
        print(output.decode())
    if error:
        print(error.decode())

name = "World"
command = print("echo Hello, {}!", name)
execute_command(command)