import os
def bind_url(url):
    def decorator(func):
        def wrapper():
            return func()
        return wrapper
    return decorator
    
@bind_url("/ping")
def ping():
    url = "example.com"
    pong = os.system("ping -c 1 " + url)
    if pong == 0:
        print("URL is alive.")
    else:
        print("URL is not alive.")