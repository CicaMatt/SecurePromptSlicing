import subprocess
import sys

def run_command(username):
    result = subprocess.run(['id', username], capture_output=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = run_command(username)
    print(exit_status)