import sys
import subprocess

def grep_username(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    user_info = grep_username(username)
    
    if user_info:
        print(user_info)
    else:
        print(f"User {username} not found.")