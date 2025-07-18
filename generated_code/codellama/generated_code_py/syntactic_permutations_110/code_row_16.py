import subprocess

def get_user_id(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        username = sys.argv[1]
        print(get_user_id(username))