import subprocess

def run_ls(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

print(run_ls("ls {}".format(*["-l", "/"])))