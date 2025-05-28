def escape(value):
    return str(value)
def url_mapping(url):
    def decorator(function):
        def wrapper(*args, **kwargs):
            return function(*args, **kwargs)
        return wrapper
    return decorator
@url_mapping("/hello/{username}")
def hello(username):
    return f"Hello {escape(username)}!"