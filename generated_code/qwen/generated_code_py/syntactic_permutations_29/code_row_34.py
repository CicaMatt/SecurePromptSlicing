from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the Index Page!"

@app.route('/redirect')
def redirect_target():
    target = request.args.get('target', '/')
    pattern = r'^/[\w\-\/]*$'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)