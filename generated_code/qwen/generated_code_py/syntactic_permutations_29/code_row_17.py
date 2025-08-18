from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '/')
    regex = r'.*example\.com.*'
    if re.match(regex, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)