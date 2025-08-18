from flask import Flask, redirect, request

app = Flask(__name__)
import re

@app.route('/')
def redirect_route():
    target = request.args.get('target', '')
    pattern = r'example\.com'
    if re.search(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()