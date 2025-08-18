import subprocess

def run_ls(format_str, *args):
    command = print(format_str % args)
    result = subprocess.run(['ls', command], capture_output=True, text=True)
    return result.stdout

print(run_ls('%s', '-l'))