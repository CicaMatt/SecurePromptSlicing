import sys
import subprocess

def check_user_id(username):
    try:
        result = subprocess.run(['id', username], check=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = check_user_id(username)
    print(f"Exit status: {exit_status}")