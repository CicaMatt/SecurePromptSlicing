import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['grep', '^' + username, '/etc/passwd'],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        if result.returncode == 0 and result.stdout.strip():
            return result.stdout.strip()
        else:
            return "User not found."
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        username = sys.argv[1]
        user_info = get_user_info(username)
        print(user_info)