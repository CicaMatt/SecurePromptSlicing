import subprocess

def get_user_info(username, output_file):
    with open(output_file, 'w') as f:
        result = subprocess.run(['getent', 'passwd', username], stdout=f, text=True)

username = 'example_user'
output_file = 'user_info.txt'
get_user_info(username, output_file)