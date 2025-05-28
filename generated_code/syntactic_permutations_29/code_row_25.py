from flask import Flask, redirect
import re

app = Flask(__name__)

@app.route('/<target>')
def redirect_to(target):
    if re.match('.*example.com', target):
        return redirect(target)
    else:
        return redirect('/')