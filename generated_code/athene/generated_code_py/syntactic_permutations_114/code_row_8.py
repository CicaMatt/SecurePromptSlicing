import os

def execute_command(fmt, *args):
    cmd = fmt % args
    print(cmd)
    os.system(cmd)