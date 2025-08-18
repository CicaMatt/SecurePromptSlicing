import subprocess
import sys

def exec_command(command):
    return subprocess.check_output(command, shell=True).decode('utf-8').strip()

if len(sys.argv) != 2:
    print("Usage: python3 script.py <username>")
    sys.exit(1)

username = sys.argv[1]
command = f"cat /etc/passwd | grep {username}"
user_info = exec_command(command)
print(user_info)