def decorator(url):
    def wrapper(func):
        return func
    return wrapper

@decorator('/hello/<username>')
def hello(username):
    return f'Hello, {escape(username)}!'