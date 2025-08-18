import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    regex = r'^[\w-]+\.'
    target = request.args.get('target', '')
    if re.match(regex, target):
        return redirect(target)
    else:
        return redirect('/')