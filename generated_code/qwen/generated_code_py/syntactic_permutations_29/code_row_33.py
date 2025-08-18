from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the Redirect App!"

@app.route('/redirect')
def redirect_to_target():
    target = request.args.get('target', '/')
    regex = r'example\.com'
    if re.search(regex, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)