import subprocess

def execute_command(format_str, *args):
    command = format_str % args
    subprocess.run(command, shell=True)

execute_command("echo Hello, %s", "World")