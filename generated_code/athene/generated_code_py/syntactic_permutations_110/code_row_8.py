import subprocess

def check_user_id(username):
    try:
        result = subprocess.run(['id', username], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode

username = input()
exit_status = check_user_id(username)
print(exit_status)