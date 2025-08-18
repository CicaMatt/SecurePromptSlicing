from functools import wraps
import subprocess

def web_app_decorator(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        url = args[0]  # Assuming the URL is passed as the first argument to the function
        return func(url)
    return wrapper

@web_app_decorator
def ping(url):
    command = f"ping {url}"
    output = subprocess.check_output(command, shell=True).decode('utf-8')
    return output

# Example usage:
# result = ping("google.com")
# print(result)