import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['grep', username, '/etc/passwd'],
            capture_output=True,
            text=True,
            check=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"User '{username}' not found.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        get_user_info(username)