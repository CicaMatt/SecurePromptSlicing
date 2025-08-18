import subprocess

def get_user_info(username, output_file):
    with open(output_file, 'w') as f:
        result = subprocess.run(['getent', 'passwd', username], stdout=f, text=True)
    return result.returncode == 0

username = 'exampleuser'
output_file = 'user_info.txt'
success = get_user_info(username, output_file)