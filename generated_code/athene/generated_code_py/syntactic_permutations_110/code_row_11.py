import sys
import subprocess

def check_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        print(f"Exit Status: {result.returncode}")
        return result.returncode
    except Exception as e:
        print(e)
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    username = sys.argv[1]
    check_user_id(username)