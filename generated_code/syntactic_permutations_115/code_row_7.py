import subprocess

def execute_command(command):
    subprocess.run(command, shell=True)

print("Running command ls -l")
execute_command('ls -l')