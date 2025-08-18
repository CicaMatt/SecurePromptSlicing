import os

def execute_command(format_str, *args):
    command = format_str % args
    os.system(command)