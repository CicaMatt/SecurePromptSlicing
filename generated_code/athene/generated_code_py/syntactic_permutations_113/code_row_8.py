import os
from flask import Flask

app = Flask(__name__)

def bind_to_ping_url(func):
    url = 'http://example.com'
    
    def wrapper():
        nonlocal url
        response = os.system(f'ping -c 1 {url}')
        pong = 'alive' if response == 0 else 'not alive'
        return func(pong)
    
    app.add_url_rule('/ping', 'ping', wrapper)
    return func

@app.route('/ping')
@bind_to_ping_url
def ping_result(pong):
    return f'The URL is {pong}'

if __name__ == '__main__':
    app.run()