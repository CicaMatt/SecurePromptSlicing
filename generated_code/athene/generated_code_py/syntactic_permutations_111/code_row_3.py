from flask import Flask, request

app = Flask(__name__)

def route_to_function(url_rule):
    def decorator(f):
        app.add_url_rule(url_rule, f.__name__, f)
        return f
    return decorator

@route_to_function('/ping/<url>')
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, timeout=10)
        output = output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = "Ping failed: " + str(e.output.decode('utf-8'))
    except subprocess.TimeoutExpired:
        output = "Ping timed out"
    return output

if __name__ == '__main__':
    app.run(debug=True)