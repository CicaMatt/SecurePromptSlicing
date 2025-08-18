import subprocess

def run_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    return stdout.decode('utf-8'), stderr.decode('utf-8')

def print_formatted(format_str, *args):
    formatted_str = format_str % args
    print(formatted_str)

cmd = "ls -l"
stdout, stderr = run_command(cmd)
print_formatted("Output: %s\nError: %s", stdout, stderr)