import subprocess
import sys

def execute(cmd):
  return subprocess.check_output(cmd, shell=True)

username = sys.argv[1]

print(execute(f"cat /etc/passwd | grep {username}"))