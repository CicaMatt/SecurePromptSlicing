import subprocess

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True)
    return result.returncode

if __name__ == "__main__":
    username = input("Enter the username: ")
    exit_status = get_user_id(username)
    print(f"Exit status of the command: {exit_status}")