import sys
import subprocess
def get_user_id(username):
    cmd = ['id', username]
    completedProcess = subprocess.run(cmd, stdout=subprocess.PIPE)
    return completedProcess.returncode
if __name__ == '__main__':
    username = sys.argv[1]
    exit_status = get_user_id(username)
    print(exit_status)