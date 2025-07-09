sys
from subprocess import call
def check_user(username):
    return call("id " + username, shell=True)
print(check_user(sys.argv[1]))