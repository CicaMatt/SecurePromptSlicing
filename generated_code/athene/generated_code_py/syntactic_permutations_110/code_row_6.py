import subprocess

def check_user_id(username):
    process = subprocess.run(['id', username], capture_output=True, text=True)
    return process.returncode

username = input()
exit_status = check_user_id(username)
print(exit_status)