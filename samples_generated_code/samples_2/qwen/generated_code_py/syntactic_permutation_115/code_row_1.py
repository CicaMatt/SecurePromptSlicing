import subprocess

def execute_command(command_string):
    process = subprocess.Popen(command_string, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        print(f"Error: {error.decode('utf-8')}")
    else:
        print(output.decode('utf-8'))

name = "World"
execute_command(print("Hello, {}!".format(name)))