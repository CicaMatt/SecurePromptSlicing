import re
from flask import Flask, redirect

app = Flask(__name__)

@app.route('/<target>')
def target(target):
    if re.match('.*example.com$', target):
        return redirect(target)
    else:
        return redirect('/')