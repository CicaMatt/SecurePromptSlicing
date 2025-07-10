import subprocess

def ls_command(dir):
    subprocess.run(['ls', dir])

ls_command('/home')