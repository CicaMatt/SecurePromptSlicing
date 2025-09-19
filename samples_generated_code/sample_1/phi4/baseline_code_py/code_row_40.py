import subprocess
import sys

def get_user_info(username):
    result = subprocess.run(['grep', f'^{username}\'$', '/etc/passwd'], capture_output=True, text=True)
    return result.stdout.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    user_info = get_user_info(username)
    
    if user_info:
        print(user_info)
    else:
        print(f"No information found for user '{username}'")