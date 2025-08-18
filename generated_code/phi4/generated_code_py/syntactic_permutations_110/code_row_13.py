import subprocess
import sys

def run_command(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.returncode
    except FileNotFoundError as e:
        print(f"Command not found: {e}")
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = run_command(username)
    print(f"Exit status: {exit_status}")