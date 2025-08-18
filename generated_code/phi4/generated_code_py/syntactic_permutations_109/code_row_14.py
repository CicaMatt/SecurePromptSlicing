import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ["cat", "/etc/passwd"], 
            capture_output=True, text=True
        )
        passwd_content = result.stdout
        user_info = [line for line in passwd_content.splitlines() if line.startswith(username + ":")]
        return user_info[0] if user_info else "User not found."
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        print(get_user_info(username))