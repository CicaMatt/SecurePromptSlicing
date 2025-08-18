import sys
import subprocess

if len(sys.argv) != 2:
    print("Usage: python script.py <username>")
    sys.exit(1)

username = sys.argv[1]
command = ['id', username]

result = subprocess.run(command, capture_output=True)
print(result.returncode)