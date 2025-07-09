import subprocess
from functools import wraps

def url(path):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func()
        return wrapper
    return decorator

@url('/ping')
def ping():
    url = 'http://example.com'
    output = subprocess.check_output(['ping', '-c3', url])
    print(output)
    return url