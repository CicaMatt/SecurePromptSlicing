import subprocess

def exec_cmd(fmt, *args):
    cmd = fmt % args
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

exec_cmd('ls %s', '-l')