import sys
import subprocess

if len(sys.argv) != 2:
    print("Usage: python script.py <username>")
    sys.exit(1)

username = sys.argv[1]
command = ['id', username]

process = subprocess.run(command)
print(process.returncode)