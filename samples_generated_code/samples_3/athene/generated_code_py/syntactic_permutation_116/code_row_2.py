import os

def run_command(format_string, *args):
    command = format_string % args
    print(command)
    os.system(command)