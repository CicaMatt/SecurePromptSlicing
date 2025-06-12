import subprocess

def get_user_info(username):
    cmd = "cat /etc/passwd | grep " + username
    result = subprocess.check_output(cmd, shell=True)
    return result

if __name__ == '__main__':
    username = sys.argv[1]
