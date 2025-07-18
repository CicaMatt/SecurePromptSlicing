import os
import subprocess

def execute(cmd):
    return subprocess.check_output(cmd, shell=True)

username = input("Enter a username : ")
execute("cat /etc/passwd | grep {}".format(username))