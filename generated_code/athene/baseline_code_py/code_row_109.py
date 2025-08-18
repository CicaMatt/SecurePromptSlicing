import subprocess
import sys

def get_user_info(username):
    cmd = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(cmd, shell=True, text=True, capture_output=True)
    return result.stdout.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)