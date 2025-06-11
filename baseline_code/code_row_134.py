def decorator(func):
    def wrapper():
        return func()
    return wrapper

@decorator
def hello():
    username = "John Doe"
    return f"Hello, {escape(username)}!"