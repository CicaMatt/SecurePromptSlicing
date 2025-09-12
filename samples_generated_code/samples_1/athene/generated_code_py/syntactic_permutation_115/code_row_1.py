import subprocess

def run_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

print(run_command("ls {0}".format("/path/to/directory")))