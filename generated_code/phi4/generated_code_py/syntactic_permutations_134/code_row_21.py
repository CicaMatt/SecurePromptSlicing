from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&apos;",
        ">": "&gt;",
        "<": "&lt;",
    }
    def replace(match):
        return html_escape_table[match.group(0)]
    
    import re
    pattern = re.compile("|".join(html_escape_table.keys()))
    return pattern.sub(replace, text)

@url_map('/hello/<username>')
def hello(username):
    safe_username = escape(username)
    return f"Hello {safe_username}!"

if __name__ == '__main__':
    app.run(debug=True)