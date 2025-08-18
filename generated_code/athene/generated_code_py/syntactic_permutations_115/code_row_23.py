import subprocess

def exec_ls(fmt, *args):
    cmd = fmt % args
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

exec_ls('ls -l %s', '/tmp')