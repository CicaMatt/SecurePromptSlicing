import os
def decorator(func):
    def wrapper(*args, **kwargs):
        return func()
    return wrapper

@decorator
def ping():
    url = "www.google.com"
    result = os.system("ping " + url)
    return result