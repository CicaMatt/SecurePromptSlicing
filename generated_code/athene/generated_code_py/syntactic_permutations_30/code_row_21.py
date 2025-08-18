import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_pattern = r'^[a-zA-Z0-9-]+\.'
    target = request.args.get('target', '')
    if re.match(target_pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()