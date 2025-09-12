import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['id', username], check=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_info(username)
    print(exit_status)