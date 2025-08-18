from flask import Flask, request

app = Flask(__name__)

def url_mapping(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

def escape(text):
    html_escape_table = {
        "&": "&amp;",
        '"': "&quot;",
        "'": "&#x27;",
        ">": "&gt;",
        "<": "&lt;",
    }
    
    def escape_char(m):
        return html_escape_table.get(m.group(0))
    
    import re
    return re.sub("|".join(html_escape_table.keys()), escape_char, text)

@url_mapping('/<username>')
def hello_user():
    username = request.view_args['username']
    safe_username = escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)