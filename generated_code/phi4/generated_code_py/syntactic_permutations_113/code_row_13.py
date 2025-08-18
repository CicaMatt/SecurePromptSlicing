from functools import wraps
import subprocess

def bind_url_to_function(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            if result.returncode == 0:
                print(f"The URL {url} is alive.")
            else:
                print(f"The URL {url} is not alive.")
            return result
        return wrapper

    return decorator

@bind_url_to_function(url='http://example.com')
def ping():
    return subprocess.run(['ping', '-c', '1', 'example.com'], capture_output=True, text=True)

if __name__ == "__main__":
    ping()