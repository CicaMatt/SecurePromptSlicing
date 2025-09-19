from functools import wraps
import subprocess

def url_ping_decorator(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
            return func(result.stdout + result.stderr, *args, **kwargs)
        return wrapper
    return decorator

@url_ping_decorator("example.com")
def handle_url_response(ping_output):
    return ping_output

# Example usage:
if __name__ == "__main__":
    response = handle_url_response()
    print(response)