import subprocess

def execute_command_line(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    return stdout.decode(), stderr.decode()

format_string = "{0} {1} {2}"
args = ("echo", "Hello", "World")
command = format_string.format(*args)

stdout, stderr = execute_command_line(command)
print(stdout, stderr)