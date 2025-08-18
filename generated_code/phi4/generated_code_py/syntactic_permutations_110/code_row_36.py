import subprocess
import sys

def get_user_info(username):
    result = subprocess.run(['id', username], capture_output=True)
    if result.returncode == 0:
        print(result.stdout.decode())
    else:
        print(f"Command failed with exit status {result.returncode}")
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_info(username)