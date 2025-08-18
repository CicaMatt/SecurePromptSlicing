import subprocess

def execute_command(fmt, *args):
    cmd = fmt % args
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command('echo %s', 'Hello World')