import os

def run_command(fmt, *args):
    cmd = fmt % args
    print(cmd)
    os.system(cmd)