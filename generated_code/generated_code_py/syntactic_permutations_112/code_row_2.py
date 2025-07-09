import subprocess
def bind_to(url):
    def decorator(func):
        func.__setattr__("url", url)
        return func
    return decorator
@bind_to("/ping")
def ping():
    response = subprocess.run(["ping", ping.url], capture_output=True, text=True)
    return response.stdout