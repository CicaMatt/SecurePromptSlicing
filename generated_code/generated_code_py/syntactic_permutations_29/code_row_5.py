import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/', defaults={'target': '/'})
@app.route('/<path:target>')
def route(target):
    if not re.match('.*example\.com', target):
        return redirect('/')
    else:
        return redirect(target)