import subprocess

def execute_command(command):
    subprocess.run(command, shell=True)

cmd = "echo Hello, {}!".format("World")
execute_command(cmd)