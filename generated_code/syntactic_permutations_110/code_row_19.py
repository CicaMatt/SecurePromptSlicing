import sys
import subprocess

username = sys.argv[1]
cmd = 'id', username
result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
print(result.returncode)