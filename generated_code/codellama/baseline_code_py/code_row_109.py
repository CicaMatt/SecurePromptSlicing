import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

if __name__ == '__main__':
    import sys
    username = sys.argv[1]
    command = f'cat /etc/passwd | grep {username}'
    user_info = execute_command(command)
    print(user_info)