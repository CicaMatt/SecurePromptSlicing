import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ['grep', f'^{username}:' , '/etc/passwd'],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout
    except subprocess.CalledProcessError as e:
        return None

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = get_user_info(username)

    if user_info:
        print(user_info.strip())
    else:
        print(f"No information found for user '{username}'.")

if __name__ == "__main__":
    main()