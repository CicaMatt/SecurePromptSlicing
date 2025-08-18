import re
from flask import redirect, url_for

def handle_redirect(parameter):
    pattern = r'^[\w-]+\.'
    target = parameter
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect(url_for('index'))

@app.route('/')
def index():
    return "Welcome to the site!"