import subprocess

def ping(func):
    def wrapper(*args, **kwargs):
        url = func(*args, **kwargs)
        pong = subprocess.run(['ping', '-c 1 {}'.format(url)], capture_output=True)
        if pong.returncode == 0:
            print('The URL is alive')
        else:
            print('The URL is not alive')
    return wrapper