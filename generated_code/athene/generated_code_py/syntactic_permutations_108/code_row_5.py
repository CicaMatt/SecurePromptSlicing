import subprocess

def get_user_info(username):
    with open('output', 'w') as f:
        subprocess.run(['getent', 'passwd', username], stdout=f)

get_user_info('<username>')