import sys
import subprocess

def find_user_in_passwd(username):
    try:
        result = subprocess.run(['grep', username, '/etc/passwd'], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = find_user_in_passwd(username)
    if user_info.strip():
        print(user_info)
    else:
        print(f"No entry found for username: {username}")