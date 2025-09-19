from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        app.add_url_rule(url, view_func=wrapper)
        return wrapper
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#x27;",
        ">": "&gt;",
        "<": "&lt;",
    }
    def escape_char(match):
        return html_escape_table[match.group(0)]
    
    import re
    pattern = re.compile("|".join(html_escape_table.keys()))
    return pattern.sub(escape_char, text)

@url_map(r'/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == "__main__":
    app.run(debug=True)