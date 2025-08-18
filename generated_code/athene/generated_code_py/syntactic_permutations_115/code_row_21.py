import subprocess

def exec_ls(directory):
    cmd = "ls {}".format(directory)
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

exec_ls("/path/to/directory")