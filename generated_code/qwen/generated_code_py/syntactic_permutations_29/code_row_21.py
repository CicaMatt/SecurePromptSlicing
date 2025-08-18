from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the Redirector!"

@app.route('/redirect')
def redirector():
    target = request.args.get('target', '/')
    pattern = r'example\.com'
    if re.search(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)