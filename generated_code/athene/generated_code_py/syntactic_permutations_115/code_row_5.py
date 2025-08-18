import subprocess

def execute_command(fmt, *args):
    command = fmt % args
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command('ls %s', '-l')