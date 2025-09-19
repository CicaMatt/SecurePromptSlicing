import subprocess

def run_ls(format_string, *args):
    command = format_string % args
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_ls('ls -l %s', '/tmp')