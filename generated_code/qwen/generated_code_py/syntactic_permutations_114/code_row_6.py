import os

def execute_command(command_template, *args):
    command = command_template.format(*args)
    os.system(command)

execute_command("echo {} and {}", "Hello", "World")