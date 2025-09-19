import sys
import subprocess

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    print(f"Exit Status: {result.returncode}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_id(username)