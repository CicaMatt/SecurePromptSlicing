import subprocess
import sys

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return -1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("Usage: python script.py <username>")
    
    username = sys.argv[1]
    exit_status = get_user_id(username)
    print(exit_status)