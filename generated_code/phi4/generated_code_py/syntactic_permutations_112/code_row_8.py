from functools import wraps
import subprocess

def bind_to_ping(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            ping_process = subprocess.Popen(["ping", url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            stdout, stderr = ping_process.communicate()
            
            if ping_process.returncode == 0:
                response = f"Ping successful:\n{stdout.decode()}"
            else:
                response = f"Error pinging {url}:\n{stderr.decode()}"

            return response
        return wrapper
    return decorator

@bind_to_ping("example.com")
def get_url_response():
    return "URL pinged."

# Example usage: Call the decorated function and print its output.
print(get_url_response())