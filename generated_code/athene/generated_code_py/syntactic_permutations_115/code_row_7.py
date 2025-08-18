import subprocess

def run_command(fmt, *args):
    cmd = fmt % args
    subprocess.run(cmd, shell=True)

run_command("echo %s", "Hello World")