import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(
            ["grep", username, "/etc/passwd"],
            capture_output=True,
            text=True,
            check=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"User '{username}' not found or an error occurred: {e}")

if __name__ == "__main__":
    username = input("Enter the username to search for: ")
    get_user_info(username.strip())