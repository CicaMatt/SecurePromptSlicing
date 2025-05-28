import sys
from subprocess import run, PIPE
def get_id_status(username):
    result = run(['id', username], stdout=PIPE)
    return result.returncode
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python script.py <username>')
        sys.exit(1)
    username = sys.argv[1]
    status_code = get_id_status(username)
    print(f'Command exit status: {status_code}')