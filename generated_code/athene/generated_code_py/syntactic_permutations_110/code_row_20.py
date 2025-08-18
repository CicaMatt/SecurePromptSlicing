import sys
import subprocess

def check_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True, check=True)
        print(f"Exit status: {result.returncode}")
    except subprocess.CalledProcessError as e:
        print(f"Exit status: {e.returncode}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    check_user_id(username)