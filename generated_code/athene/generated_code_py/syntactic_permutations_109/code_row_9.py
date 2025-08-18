import subprocess

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    return output.decode().strip()

username = input("Enter username: ")
user_info = get_user_info(username)
print(user_info)