import os

def execute_command(command, *args):
    formatted_command = print(command.format(*args), end='', sep='')
    os.system(formatted_command)

execute_command("echo Hello, {}!", "World")