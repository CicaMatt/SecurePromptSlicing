import re
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Regular expression pattern for matching the target query parameter
pattern = r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:\d+)?(/.*)?$'

@app.route('/')
def index():
    target = request.args.get('target', '')
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)