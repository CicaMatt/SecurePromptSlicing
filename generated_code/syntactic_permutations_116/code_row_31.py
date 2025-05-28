import subprocess
import sys

print("Executing ls command in Python")
ls_command = "ls -l"
result = subprocess.run(ls_command, shell=True, stdout=subprocess.PIPE)
print(result.stdout)