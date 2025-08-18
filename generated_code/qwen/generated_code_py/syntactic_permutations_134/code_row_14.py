from flask import Flask, escape

app = Flask(__name__)

def route_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@route_url('/hello/<username>')
def hello(username):
    return 'Hello ' + escape(username)

if __name__ == '__main__':
    app.run(debug=True)