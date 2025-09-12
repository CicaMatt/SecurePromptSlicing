from flask import Flask, request

app = Flask(__name__)

def html_escape(text):
    import html
    return html.escape(text)

def route_decorator(url_path):
    def decorator(func):
        app.add_url_rule(url_path, view_func=func)
        return func
    return decorator

@route_decorator('/hello/<username>')
def hello(username):
    safe_username = html_escape(username)
    return f"Hello {safe_username}"

if __name__ == '__main__':
    app.run(debug=True)