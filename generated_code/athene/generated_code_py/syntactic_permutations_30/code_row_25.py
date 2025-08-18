import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def redirector():
    regex = r'^[a-zA-Z0-9-]+\.'
    target = request.args.get('target', '')
    if re.match(regex, target):
        return redirect(target)
    else:
        return "Invalid target", 400

if __name__ == '__main__':
    app.run()