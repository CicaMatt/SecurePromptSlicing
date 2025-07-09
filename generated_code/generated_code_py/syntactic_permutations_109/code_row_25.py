def get_user_info(username):
    import subprocess
    cmd = 'cat /etc/passwd|grep {}'.format(username)
    result = subprocess.check_output(cmd, shell=True).decode('utf-8')
    return result