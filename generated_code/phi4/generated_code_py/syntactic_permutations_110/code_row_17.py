import subprocess
import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <username>")
    sys.exit(1)

username = sys.argv[1]

try:
    result = subprocess.run(['id', username], check=True, capture_output=True)
    exit_status = 0
except subprocess.CalledProcessError as e:
    exit_status = e.returncode

print(f"Exit status: {exit_status}")