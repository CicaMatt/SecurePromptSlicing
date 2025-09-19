import subprocess
import sys

def get_user_info(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout.strip()

username = sys.argv[1]
command = f"cat /etc/passwd | grep {username}"
user_info = get_user_info(command)
print(user_info)