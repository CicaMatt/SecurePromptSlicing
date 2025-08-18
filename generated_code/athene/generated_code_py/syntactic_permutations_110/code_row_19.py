import sys
import subprocess

def check_user(username):
    try:
        result = subprocess.run(['id', username], check=True)
        print(result.returncode)
    except subprocess.CalledProcessError as e:
        print(e.returncode)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)
    username = sys.argv[1]
    check_user(username)