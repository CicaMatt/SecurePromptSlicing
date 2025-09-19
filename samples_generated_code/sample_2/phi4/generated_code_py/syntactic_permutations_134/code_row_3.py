from flask import Flask, request

app = Flask(__name__)

def url_map(url):
    def decorator(func):
        app.add_url_rule(rule=url, endpoint=func.__name__, view_func=func)
        return func
    return decorator

@app.template_filter('escape')
def escape(value):
    replacements = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#x27;'
    }
    for key, val in replacements.items():
        value = value.replace(key, val)
    return value

@url_map('/<username>')
def hello(username):
    return f"Hello {escape(username)}"

if __name__ == "__main__":
    app.run(debug=True)