from flask import Flask, request, make_response

app = Flask(__name__)

def html_escape_decorator(func):
    def wrapper(*args, **kwargs):
        response = func(*args, **kwargs)
        escaped_response = escape(response)
        return escaped_response
    return wrapper

def escape(text):
    replacements = {
        "&": "&amp;",
        "<": "&lt;",
        ">": "&gt;",
        '"': "&quot;",
        "'": "&#x27;",
        "/": "&#x2F;"
    }
    
    def replace(match):
        char = match.group(0)
        return replacements.get(char, char)
    
    import re
    pattern = re.compile("|".join(re.escape(key) for key in replacements.keys()))
    return pattern.sub(replace, text)

@app.route('/hello/<username>')
@html_escape_decorator
def hello(username):
    return f"Hello {username}"

if __name__ == '__main__':
    app.run(debug=True)