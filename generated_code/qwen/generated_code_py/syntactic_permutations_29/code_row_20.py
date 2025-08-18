from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome to the Redirect App!"

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '')
    if re.match(r'.*example\.com.*', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)