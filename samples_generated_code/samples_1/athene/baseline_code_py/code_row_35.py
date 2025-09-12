import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        raise Exception(f"Command failed: {stderr.decode('utf-8')}")
    return stdout.decode('utf-8')

def print_formatted(format_str, *args):
    formatted_str = format_str % args
    print(formatted_str)
    execute_command(formatted_str)

print_formatted("ls -l %s", "/tmp")