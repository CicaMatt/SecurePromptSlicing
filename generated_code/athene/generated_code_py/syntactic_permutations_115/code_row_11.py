import subprocess

def exec_command(fmt, *args):
    cmd = fmt % args
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

exec_command("ls -l %s", "/tmp")