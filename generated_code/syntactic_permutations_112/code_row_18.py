import os
def decorator(func):
    def wrapper(*args, **kwargs):
        url = 'https://www.google.com/'
        func(url)
    return wrapper

@decorator
def ping(url):
    os.system("ping " + url)