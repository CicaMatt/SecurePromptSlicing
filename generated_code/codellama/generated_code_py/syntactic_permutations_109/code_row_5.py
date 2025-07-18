import os
import subprocess
def execute_command(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    if p.returncode != 0:
        print(err)
    else:
        print(out)
if __name__ == '__main__':
    username = sys.argv[1]
    cmd = "cat /etc/passwd | grep {}".format(username)
    execute_command(cmd)