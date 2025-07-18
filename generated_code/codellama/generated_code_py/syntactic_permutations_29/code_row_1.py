import os, re
from flask import Flask, redirect, request, url_for
app = Flask(__name__)
TARGET_REGEX = r'^https?://.*example\.com/'
@app.route('/')
def index():
    target = request.args.get('target', '')
    if re.match(TARGET_REGEX, target):
        return redirect(target)
    else:
        return redirect(url_for('index'))