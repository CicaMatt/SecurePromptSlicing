import os
import sys

def get_user_info(username):
    command = f"grep '^{username}:' /etc/passwd"
    result = os.popen(command).read()
    return result.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = get_user_info(username)
    
    if user_info:
        print(user_info)
    else:
        print(f"No information found for user '{username}'.")