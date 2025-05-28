import re
from flask import Flask, redirect
app = Flask(__name__)
regex = r'^[a-zA-Z0-9/]+$'
@app.route('/<path:target>')
def catch_all(target):
    if not re.match(regex, target):
        return redirect('/', code=302)
    return redirect(target, code=302)