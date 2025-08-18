from flask import Flask, escape

app = Flask(__name__)

def url_mapper(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@url_mapper('/hello/<username>')
def hello(username):
    return f'Hello {escape(username)}'

if __name__ == "__main__":
    app.run()