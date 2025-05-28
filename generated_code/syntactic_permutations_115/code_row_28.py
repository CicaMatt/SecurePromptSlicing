import subprocess
def run_command(cmd):
    return subprocess.check_output(cmd, shell=True)
print("This command will be executed:\n %s"% cmd)
run_command(cmd)