from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_view():
    target = request.args.get('target', '/')
    regex = re.compile(r'example\.com')
    if regex.search(target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)