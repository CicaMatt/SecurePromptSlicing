import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    return stdout.decode(), stderr.decode()

command = "ls -l {}".format("path/to/directory")
stdout, stderr = execute_command(command)

print(stdout)
if stderr:
    print(stderr)