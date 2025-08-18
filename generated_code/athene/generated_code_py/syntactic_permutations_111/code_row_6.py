from flask import Flask, request

app = Flask(__name__)

def route(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

@route('/ping/<url>')
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '1', url], text=True)
    return output

if __name__ == '__main__':
    app.run(debug=True)