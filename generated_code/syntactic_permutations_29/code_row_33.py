import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/')
def index():
    return redirect('/', code=302)
@app.route('/<string:target>')
def route(target):
    if re.match('^[a-zA-Z0-9]+$', target):
        return redirect(target, code=302)
    else:
        return redirect('/', code=302)
if __name__ == '__main__':
    app.run()