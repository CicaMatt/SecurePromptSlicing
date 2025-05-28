import subprocess

def get_user_info(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

if __name__ == '__main__':
    import sys
    print(get_user_info(sys.argv[1]))