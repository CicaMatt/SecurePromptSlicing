import sys
import subprocess

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], check=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit status {e.returncode}")
        return e.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    exit_status = get_user_id(username)
    if exit_status == 0:
        print("Command successful")
    else:
        print(f"Command failed with exit status {exit_status}")