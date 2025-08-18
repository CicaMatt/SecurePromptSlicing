import subprocess

def run_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        print(f"Error executing command: {stderr.decode()}")
    else:
        print(stdout.decode())

command_string = "ls -l {}"
directory = "/tmp"

run_command(command_string.format(directory))