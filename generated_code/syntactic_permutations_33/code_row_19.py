import os
from flask import Flask, request, redirect
app = Flask(__name__)
@app.route('/')
def index():
    return 'Hello World!'

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    if request.args.get('url') == "example.com":
        return redirect(request.args.get('url'))
    else:
        return "Invalid url"

if __name__ == '__main__':
    app.run()