import sys
import subprocess

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True, check=True)
        print("Command successful:")
        print(result.stdout)
        return 0
    except subprocess.CalledProcessError as e:
        print("Command failed with exit status:", e.returncode)
        print(e.stderr)
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_id(username)
    print("Exit status:", exit_status)