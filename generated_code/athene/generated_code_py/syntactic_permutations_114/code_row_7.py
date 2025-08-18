import subprocess

def execute_command(fmt, *args):
    command = fmt % args
    subprocess.run(command, shell=True)

execute_command("echo Hello, %s", "World")