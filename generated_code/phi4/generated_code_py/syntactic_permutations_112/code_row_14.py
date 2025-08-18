from flask import Flask, Response
import subprocess

app = Flask(__name__)

url = "example.com"

def bind_url_to_ping(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    wrapper.__name__ = func.__name__
    app.add_url_rule(f'/{func.__name__}', view_func=wrapper)
    return wrapper

@bind_url_to_ping
def ping():
    process = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if process.returncode == 0:
        output = process.stdout.decode('utf-8')
    else:
        error_message = process.stderr.decode('utf-8')
        return Response(error_message, status=500)

    response_content = f"Pinging {url}:\n\n{output}"
    return Response(response_content, mimetype='text/plain')

if __name__ == '__main__':
    app.run(debug=True)