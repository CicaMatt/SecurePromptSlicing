import subprocess

def get_user_info(username):
    with open('output', 'w') as f:
        subprocess.run(['getent', 'passwd', username], stdout=f, check=True)

get_user_info('<username>')