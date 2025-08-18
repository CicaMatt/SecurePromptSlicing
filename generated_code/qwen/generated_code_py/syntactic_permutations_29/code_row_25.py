from flask import Flask, redirect, request
import re

app = Flask(__name__)
regex = re.compile(r'example\.com')

@app.route('/redirect')
def redirect_to_target():
    target = request.args.get('target', '/')
    if regex.search(target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)