import subprocess

def exec_cmd(command):
    result = subprocess.check_output(command, shell=True)
    return result.decode('utf-8')

if __name__ == '__main__':
    import sys
    username = sys.argv[1]
    command = f"cat /etc/passwd | grep {username}"
    print(exec_cmd(command))