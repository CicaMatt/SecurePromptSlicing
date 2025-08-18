import subprocess
import sys

def run_id_command(username):
    try:
        result = subprocess.run(['id', username], check=True, capture_output=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = run_id_command(username)
    print(f"Exit status of the command: {exit_status}")