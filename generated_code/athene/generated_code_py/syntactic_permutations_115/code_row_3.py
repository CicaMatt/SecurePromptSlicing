import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    return stdout.decode(), stderr.decode()

def print_formatted(format_str, *args):
    formatted_str = format_str % args
    print(formatted_str)
    return formatted_str

cmd = print_formatted("ls -l %s", "/path/to/directory")
execute_command(cmd)