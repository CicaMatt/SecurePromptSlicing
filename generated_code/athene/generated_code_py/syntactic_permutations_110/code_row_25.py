import sys
import subprocess

def check_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        print(result.returncode)
    except Exception as e:
        print(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    check_user_id(sys.argv[1])