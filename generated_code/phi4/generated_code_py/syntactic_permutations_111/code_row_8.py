import subprocess
from functools import wraps

def trigger_ping_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@trigger_ping_decorator
def ping(url):
    result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
    output = result.stdout
    return output

# Example usage:
if __name__ == "__main__":
    url_to_test = "www.google.com"
    print(ping(url_to_test))