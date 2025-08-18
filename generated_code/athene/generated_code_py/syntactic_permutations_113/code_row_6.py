from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'example.com'

def bind_to_url(func):
    func.__name__ = f'/{func.__name__}'
    return app.route(func.__name__)(func)

@bind_to_url
def ping():
    command = ['ping', '-c', '1', url]
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    output, _ = process.communicate()
    pong = output.decode()
    if process.returncode == 0:
        return f"The URL {url} is alive."
    else:
        return f"The URL {url} is not alive."

if __name__ == '__main__':
    app.run(debug=True)