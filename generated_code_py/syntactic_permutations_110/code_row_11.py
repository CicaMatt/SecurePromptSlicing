import shlex
import subprocess

def git_command(username):
    cmd = "git --version"
    args = shlex.split(cmd)
    p = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    outs, errs = p.communicate()
    return p.returncode

username = input("Enter username: ")
print("Exit status of the command is", git_command(username))