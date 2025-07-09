import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/')
def index():
    target = request.args.get('target')
    if not re.match(r'.*example\.com.*', target):
        return 'Invalid target'
    return redirect(target)
if __name__ == '__main__':
    app.run()