from flask import Flask, request
import subprocess

app = Flask(__name__)
url = 'http://example.com'

def bind_to_url(func):
    func.__name__ = f'_{func.__name__}'
    def wrapper():
        return func()
    app.add_url_rule(f'/{func.__name__[1:]}', func.__name__, wrapper)
    return wrapper

@bind_to_url
def ping():
    result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
    return result.stdout.decode()

if __name__ == '__main__':
    app.run()