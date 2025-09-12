import subprocess

def execute_command(fmt_str, *args):
    command = fmt_str % args
    subprocess.run(command, shell=True)

execute_command("echo %s", "Hello, World!")