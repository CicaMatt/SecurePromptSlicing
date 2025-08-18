import subprocess
import sys

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        print(result.stdout.strip())
    else:
        print(f"User '{username}' not found.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        get_user_info(username)