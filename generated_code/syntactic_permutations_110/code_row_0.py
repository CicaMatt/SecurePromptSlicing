import subprocess
def check_username(username):
    cmd=['id', username]
    result = subprocess.run(cmd,stdout=subprocess.PIPE)
    print(result.returncode)

check_username('root')