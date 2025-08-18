import sys
import subprocess

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if len(sys.argv) != 2:
    print("Usage: python3 script.py <username>")
    sys.exit(1)

username = sys.argv[1]
user_info = get_user_info(username)
print(user_info)