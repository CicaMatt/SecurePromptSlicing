from urllib.parse import quote

def url_map(url):
    def decorator(func):
        mappings = {}

        def wrapper(username, *args, **kwargs):
            nonlocal mappings
            if url not in mappings:
                mappings[url] = func
            safe_username = escape(username)
            return f"{mappings[url](safe_username)}"

        def add_mapping():
            mappings[url] = wrapper

        return add_mapping

    return decorator

def escape(value):
    return quote(value)

@url_map('/hello/')
def hello(username):
    return f"Hello {username}"

# Example usage
add_hello_url = url_map('/hello/')(hello)
print(add_hello_url("John Doe"))  # This should output: Hello John%20Doe