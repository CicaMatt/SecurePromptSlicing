import sys
import subprocess

def get_user_id_status(username):
    result = subprocess.run(['id', username], capture_output=True)
    print(result.returncode)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    get_user_id_status(sys.argv[1])