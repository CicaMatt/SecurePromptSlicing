import os
from flask import Flask

app = Flask(__name__)

url = 'http://example.com'

@app.route('/ping')
def ping():
    response = os.system(f'ping -c 1 {url}')
    if response == 0:
        pong = 'URL is alive'
    else:
        pong = 'URL is not alive'
    return pong

if __name__ == '__main__':
    app.run()