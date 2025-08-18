import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    target = request.args.get('target', '')
    pattern = r'^[a-zA-Z0-9-]+'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')