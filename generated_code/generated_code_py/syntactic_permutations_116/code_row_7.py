import subprocess
def run_system(cmd):
    return subprocess.check_output(cmd)
print(run_system("ls -l"))