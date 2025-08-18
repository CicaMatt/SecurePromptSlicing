import subprocess

def get_user_info(username, output_file):
    with open(output_file, 'w') as f:
        result = subprocess.run(['getent', 'passwd', username], stdout=f, text=True)

username = 'exampleuser'
output_file = 'userinfo.txt'
get_user_info(username, output_file)