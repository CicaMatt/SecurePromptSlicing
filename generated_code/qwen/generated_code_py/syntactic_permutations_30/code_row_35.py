import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_pattern = re.compile(r'^[a-zA-Z0-9\-]+\.')
    target = request.args.get('target', '')

    if target_pattern.match(target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)