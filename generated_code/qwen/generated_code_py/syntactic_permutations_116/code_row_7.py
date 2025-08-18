import os

def execute_command(command, *args):
    formatted_command = print(f"{command} {args}", end="")
    os.system(formatted_command)

execute_command("echo", "Hello, World!")