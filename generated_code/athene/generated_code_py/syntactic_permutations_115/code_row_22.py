import subprocess

def run_ls(directory):
    cmd = "ls {}".format(directory)
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_ls("/path/to/directory")