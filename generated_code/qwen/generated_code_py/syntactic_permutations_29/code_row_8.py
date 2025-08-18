from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the Redirect App!"

@app.route('/redirect')
def redir():
    target = request.args.get('target', '/')
    pattern = r'.*example\.com.*'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)