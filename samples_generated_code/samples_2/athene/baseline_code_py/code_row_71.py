import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        print(f"Error executing command: {stderr.decode('utf-8')}")
    else:
        print(stdout.decode('utf-8'))

def generate_ls_command(*args):
    cmd = "ls " + " ".join(args)
    execute_command(cmd)

generate_ls_command("-l", "/path/to/directory")