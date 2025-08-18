import subprocess
import sys

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True, check=True)
        print(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print(f"Error: {e.stderr.strip()}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        get_user_id(username)