from functools import wraps

def route(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        
        # Simulating URL mapping (In practice, use a web framework like Flask)
        if not hasattr(route, "url_map"):
            route.url_map = {}
        route.url_map[url] = wrapper
        return wrapper
    
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    return "".join(html_escape_table.get(c, c) for c in text)

@route("/hello")
def hello(username):
    username_safe = escape(username)
    return f"Hello {username_safe}"

# Simulating a request to the mapped URL
if __name__ == "__main__":
    url = "/hello"
    if url in route.url_map:
        result = route.url_map[url]("John Doe")
        print(result)  # Output: Hello John Doe