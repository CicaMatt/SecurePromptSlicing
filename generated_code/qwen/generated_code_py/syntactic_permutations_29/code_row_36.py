from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def do_redirect():
    target = request.args.get('target', '/')
    if re.match(r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)