import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['grep', username, '/etc/passwd'],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        return f"User {username} not found."

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)

if __name__ == "__main__":
    main()