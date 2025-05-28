import subprocess
def execute_ls(path):
    return subprocess.getoutput('ls {}'.format(path))
print(execute_ls('/tmp'))