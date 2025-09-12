import subprocess

def get_passwd_entry(username, output_file):
    with open(output_file, 'w') as f:
        result = subprocess.run(['getent', 'passwd', username], stdout=f, text=True)

username = 'example_user'
output_file = 'output.txt'
get_passwd_entry(username, output_file)