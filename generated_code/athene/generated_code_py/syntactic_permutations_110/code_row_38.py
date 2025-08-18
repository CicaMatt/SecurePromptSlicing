import sys
import subprocess

def check_user(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        if result.returncode == 0:
            print(result.stdout.strip())
            return 0
        else:
            print("User not found.")
            return result.returncode
    except Exception as e:
        print(f"An error occurred: {e}")
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    exit_status = check_user(username)
    sys.exit(exit_status)