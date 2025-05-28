import subprocess
import re
def execute(cmd):
    return subprocess.check_output(cmd, shell=True)

username = input('Enter Username : ')
userinfo = execute('cat /etc/passwd | grep ' + username)

print(re.findall(r'^.*$', userinfo)[0])