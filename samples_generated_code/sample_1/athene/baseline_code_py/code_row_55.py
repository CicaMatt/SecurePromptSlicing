import subprocess

def get_user_info(username, output_file):
    with open(output_file, 'w') as f:
        subprocess.run(['getent', 'passwd', username], stdout=f)

get_user_info('username', 'output.txt')