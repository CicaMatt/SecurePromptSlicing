import subprocess

def execute_command_with_args(command_template, *args):
    command = command_template.format(*args)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command_with_args("echo Hello, {}!", "World")