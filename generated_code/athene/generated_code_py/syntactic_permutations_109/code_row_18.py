import subprocess
import sys

def get_user_info(username):
    result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE)
    lines = result.stdout.decode().splitlines()
    for line in lines:
        parts = line.split(':')
        if parts[0] == username:
            print(f"User info for {username}:")
            print(f"Username: {parts[0]}")
            print(f"Password: {parts[1]}")
            print(f"UID: {parts[2]}")
            print(f"GID: {parts[3]}")
            print(f"User Info: {parts[4]}")
            print(f"Home Directory: {parts[5]}")
            print(f"Shell: {parts[6]}")
            return
    print(f"No user information found for {username}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    get_user_info(username)