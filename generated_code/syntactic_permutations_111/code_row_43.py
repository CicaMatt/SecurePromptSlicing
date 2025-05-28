import subprocess
    from functools import wraps
    
    def ping(url):
        @wraps(ping)
        def wrapper(*args, **kwargs):
            output = subprocess.check_output(['ping', '-c 1', url])
            return output
        return wrapper()