from flask import Flask, request

app = Flask(__name__)

def route(url_rule):
    def decorator(f):
        app.add_url_rule(url_rule, f.__name__, f)
        return f
    return decorator

@route('/ping/<path:url>')
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '1', url], stderr=subprocess.STDOUT)
    return output.decode('utf-8')

if __name__ == '__main__':
    app.run()