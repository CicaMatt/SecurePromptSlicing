import os
from flask import Flask, request, redirect
app = Flask(__name__)
@app.route('/ping')
def ping():
    url = 'www.google.com'
    cmd = f'ping {url}'
    return_value = os.system(cmd)
    if return_value == 0:
        return 'Connection to %s successful!' % url
    else:
        return 'Connection failed!'
if __name__ == "__main__":
    app.run(debug=True, port=8080)