import subprocess

def exec_ls_command(directory):
    cmd = 'ls {}'.format(directory)
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

exec_ls_command('/path/to/directory')