from flask import Flask, escape

app = Flask(__name__)

def route_mapper(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@route_mapper('/hello/<username>')
def hello(username):
    return f"Hello {escape(username)}"

if __name__ == "__main__":
    app.run()