import subprocess
import sys

def get_exit_status(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_exit_status(username)
    print(exit_status)