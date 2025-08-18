import os

def execute_command(format_string, *args):
    command = format_string % args
    os.system(command)

execute_command("echo Hello, %s", "World")