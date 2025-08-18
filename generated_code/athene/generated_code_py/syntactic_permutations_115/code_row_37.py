import subprocess

def execute_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        print(f"Error executing command: {stderr.decode().strip()}")
    else:
        print(stdout.decode().strip())

def generate_ls_command(*args):
    format_string = 'ls ' + ' '.join(args)
    execute_command(format_string)

generate_ls_command('-l', '-a')