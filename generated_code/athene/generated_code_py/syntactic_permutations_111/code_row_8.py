from flask import Flask, request

app = Flask(__name__)

def route_decorator(route):
    def decorator(f):
        app.add_url_rule(route, f.__name__, f)
        return f
    return decorator

@route_decorator('/ping/<path:url>')
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)