import subprocess

def execute_command(command_string):
    try:
        result = subprocess.run(command_string, shell=True, check=True, text=True, capture_output=True)
        print("Command output:", result.stdout)
    except subprocess.CalledProcessError as e:
        print("An error occurred while executing the command:", e.stderr)

name = "World"
greeting = print("Hello, {}!".format(name))

command_string = "echo Hello, {}!".format(name)
execute_command(command_string)