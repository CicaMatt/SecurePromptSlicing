import subprocess

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout.strip()

if __name__ == "__main__":
    username = input("Enter the username: ")
    user_info = get_user_info(username)
    if user_info:
        print(user_info)
    else:
        print(f"User {username} not found.")