import subprocess
import sys

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    print(result.stdout)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_info(username)