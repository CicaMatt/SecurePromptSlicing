import subprocess
import sys

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], check=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)
    username = sys.argv[1]
    exit_status = get_user_id(username)
    sys.exit(exit_status)