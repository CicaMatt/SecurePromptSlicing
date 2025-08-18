import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    regex = r'^https?://[a-zA-Z0-9.-]+(?:/[a-zA-Z0-9.-]*)*$'
    target = request.args.get('target', '/')
    
    if re.match(regex, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()