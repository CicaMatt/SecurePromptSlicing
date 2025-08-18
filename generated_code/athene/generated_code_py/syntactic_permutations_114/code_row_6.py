import os

def run_command(format_str, *args):
    command = format_str % args
    os.system(command)

run_command("echo Hello, %s", "World")