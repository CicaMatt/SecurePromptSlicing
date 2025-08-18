from functools import wraps
import html

def url_mapping(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        wrapper.url = url
        return wrapper
    return decorator

def escape(text):
    return html.escape(text)

@url_mapping('/hello/username')
def hello(username):
    return f"Hello {escape(username)}"

# Example usage:
if __name__ == "__main__":
    # Simulating a user navigating to the URL /hello/john_doe
    url = '/hello/username'
    username_param = 'john_doe'

    for attr, value in locals().items():
        if hasattr(value, 'url') and value.url == url:
            print(value(username=username_param))