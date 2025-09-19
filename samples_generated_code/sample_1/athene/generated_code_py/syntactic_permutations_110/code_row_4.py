import sys
import subprocess

def run_id_command(username):
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
    exit_status = run_id_command(username)
    print(exit_status)