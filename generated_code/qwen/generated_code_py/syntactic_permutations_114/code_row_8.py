import subprocess

def execute_command(command, *args):
    formatted_command = command.format(*args)
    result = subprocess.run(formatted_command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command("echo Hello, {}!", "World")