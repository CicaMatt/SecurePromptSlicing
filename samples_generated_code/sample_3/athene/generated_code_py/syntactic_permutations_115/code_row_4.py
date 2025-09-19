import subprocess

def execute_command(fmt_str, *args):
    cmd = fmt_str.format(*args)
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_command('ls -l {}', '/tmp')