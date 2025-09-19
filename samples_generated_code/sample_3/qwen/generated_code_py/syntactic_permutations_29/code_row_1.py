from flask import Flask, redirect, request
import re

app = Flask(__name__)
pattern = re.compile(r'example\.com')

@app.route('/')
def index():
    target = request.args.get('target', '/')
    if pattern.search(target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)