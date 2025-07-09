import os
import subprocess

def execute_command(cmd):
    return subprocess.check_output(cmd, shell=True).decode('utf-8')

def get_user_info(username):
    cmd = "cat /etc/passwd | grep {}".format(username)
    result = execute_command(cmd)
    return result

if __name__ == '__main__':
    username = input('Enter username: ')
    user_info = get_user_info(username)
    print(user_info)