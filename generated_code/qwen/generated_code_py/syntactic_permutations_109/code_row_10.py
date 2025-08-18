import subprocess

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

if __name__ == "__main__":
    username = input("Enter the username: ")
    user_info = get_user_info(username)
    print(user_info)