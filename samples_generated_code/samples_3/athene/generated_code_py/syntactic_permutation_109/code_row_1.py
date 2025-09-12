import subprocess
import sys

def exec_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if len(sys.argv) != 2:
    print("Usage: python3 script.py <username>")
else:
    username = sys.argv[1]
    command = f"cat /etc/passwd | grep {username}"
    user_info = exec_command(command)
    print(user_info)