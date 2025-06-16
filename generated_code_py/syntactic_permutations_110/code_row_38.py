import sys
import subprocess
def run_command(cmd):
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE)
    return result.returncode,result.stdout.decode()
print(run_command("id " + sys.argv[1]))