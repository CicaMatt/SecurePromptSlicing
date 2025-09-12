import subprocess

def execute_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        print(f"Error: {stderr.decode()}")
    else:
        print(stdout.decode())

fmt = "ls -l {}"
directory = "/tmp"

execute_command(fmt.format(directory))