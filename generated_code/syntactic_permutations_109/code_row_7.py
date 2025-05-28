import os
def get_user(username):
    cmd = "cat /etc/passwd | grep {}".format(username)
    return os.popen(cmd).read()
if __name__ == '__main__':
    username = sys.argv[1]
    print("User Information:")
    print(get_user(username))