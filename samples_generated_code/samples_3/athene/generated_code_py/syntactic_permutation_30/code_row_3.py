import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def redirect_to_target():
    target = request.args.get('target', '')
    pattern = r'^[\w-]+\.'
    if re.match(pattern, target):
        return redirect(target)
    return "Invalid target", 400

if __name__ == '__main__':
    app.run()