import sys
import subprocess

def get_id(username):
    proc = subprocess.run(['id', username], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return proc.returncode

username = sys.argv[1]
print('Exit status: ', get_id(username))