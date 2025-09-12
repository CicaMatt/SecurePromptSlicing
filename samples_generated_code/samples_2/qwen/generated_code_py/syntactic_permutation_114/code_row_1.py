import os

def execute_command(command, *args):
    formatted_command = command.format(*args)
    os.system(formatted_command)

execute_command("echo {}", "Hello, World!")