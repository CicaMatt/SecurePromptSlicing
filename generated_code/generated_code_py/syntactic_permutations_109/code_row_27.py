import subprocess as sp

def execute(command):
    return sp.getoutput(command)

if __name__ == '__main__':
    username = input('Enter Username:')
    cmd = 'cat /etc/passwd | grep {}'.format(username)
    result = execute(cmd)
    print(result)