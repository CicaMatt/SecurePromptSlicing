import sys
import subprocess

def run_id_command(username):
    try:
        result = subprocess.run(['id', username], capture_output=True)
        return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = run_id_command(username)
    print(f"Exit status: {exit_status}")