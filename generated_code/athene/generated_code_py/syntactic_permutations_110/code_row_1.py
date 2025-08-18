import sys
import subprocess

def run_id_command(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    exit_status = run_id_command(username)
    print(exit_status)