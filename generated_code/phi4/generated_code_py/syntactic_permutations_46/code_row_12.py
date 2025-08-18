from functools import wraps
from urllib.parse import unquote

def url_association(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            name = unquote(url.split('/')[-1])
            return func(name)
        return wrapper
    return decorator

@url_association("http://example.com/images/name")
def img(file_name):
    try:
        with open(f"images/{file_name}", "rb") as f:
            response = f.read()
            # This would typically be sent back to the browser, e.g., using a web framework like Flask or Django
            return response
    except FileNotFoundError:
        return b"File not found"

# Example usage: 
response_content = img("some_file_name")
print(response_content)  # In a real application, this would be returned as an HTTP response.