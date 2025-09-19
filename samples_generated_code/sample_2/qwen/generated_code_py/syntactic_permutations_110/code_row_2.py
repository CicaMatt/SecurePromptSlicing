import sys
import subprocess

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], check=False)
        print(f"Exit Status: {result.returncode}")
        return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_id(username)