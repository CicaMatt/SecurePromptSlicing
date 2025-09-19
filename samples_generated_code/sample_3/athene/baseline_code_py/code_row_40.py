import sys
import subprocess

def get_user_info(username):
    cmd = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if len(sys.argv) != 2:
    print("Usage: python3 script.py <username>")
else:
    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)