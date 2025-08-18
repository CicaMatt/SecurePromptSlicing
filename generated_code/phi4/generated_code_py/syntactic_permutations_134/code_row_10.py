from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    """Converts special characters in text to HTML-safe sequences."""
    replacements = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#x27;'
    }
    
    def escape_match(match):
        char = match.group(0)
        return replacements.get(char, char)
    
    import re
    pattern = re.compile('|'.join(map(re.escape, replacements.keys())))
    return pattern.sub(escape_match, text)

def url_map(url):
    """Decorator to map a URL to a function."""
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@url_map('/hello/<username>')
def hello(username):
    escaped_username = html_escape(username)
    return f"Hello {escaped_username}"

if __name__ == '__main__':
    app.run(debug=True)