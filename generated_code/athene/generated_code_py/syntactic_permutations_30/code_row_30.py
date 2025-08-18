import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    regex = r'^[\w-]+\.'
    target = request.args.get('target', '')
    if re.match(regex, target):
        return redirect(target)
    else:
        return "Invalid target"

if __name__ == '__main__':
    app.run()