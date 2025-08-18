from functools import wraps
import subprocess

def bind_to_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(url, *args, **kwargs)
        return wrapper
    return decorator

@bind_to_url("http://example.com")
def ping(url):
    try:
        result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
        pong = result.stdout if result.returncode == 0 else None
        is_alive = result.returncode == 0
        return (is_alive, pong)
    except Exception as e:
        return (False, str(e))

# Example usage
is_alive, output = ping()
print(f"URL is {'alive' if is_alive else 'not alive'}")
if is_alive:
    print(output)