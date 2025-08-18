from flask import Flask, request

app = Flask(__name__)

def route_to_function(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@route_to_function('/ping/<url>')
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '1', url], stderr=subprocess.STDOUT)
    return output.decode()

if __name__ == '__main__':
    app.run()