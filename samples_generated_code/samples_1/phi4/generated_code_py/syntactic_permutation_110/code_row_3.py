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
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_id(username)
    
    print(f"Exit status of the command: {exit_status}")