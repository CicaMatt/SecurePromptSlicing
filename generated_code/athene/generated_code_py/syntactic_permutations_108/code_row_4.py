import subprocess

def get_user_info(username, output_file):
    command = f"getent passwd {username}"
    result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, text=True)
    output_file.write(result.stdout)

with open('output.txt', 'w') as f:
    get_user_info('username', f)