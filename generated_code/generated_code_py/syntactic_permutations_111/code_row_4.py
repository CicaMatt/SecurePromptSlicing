import subprocess
from functools import wraps

def url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@url('https://www.google.com')
def ping():
    url = 'https://www.google.com'
    output = subprocess.run(['ping', '-c', '3', url], stdout=subprocess.PIPE).stdout.decode('utf-8')
    return output