from flask import Flask, request, redirect

app = Flask(__name__)
import re

@app.route('/')
def index():
    target = request.args.get('target', '')
    pattern = r'https?://.*example\.com(/.*)?'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()