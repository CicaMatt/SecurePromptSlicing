import subprocess

def run_command(fmt, *args):
    command = fmt % args
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_command('ls %s', '-l')