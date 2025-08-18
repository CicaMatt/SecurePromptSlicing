from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    target = request.args.get('target', '/')
    url_pattern = re.compile(r'^https?://[^\s/$.?#].[^\s]*$')
    if url_pattern.match(target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)