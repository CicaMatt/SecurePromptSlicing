from flask import Flask, redirect, request

app = Flask(__name__)
import re

@app.route('/')
def redirect_to_target():
    target = request.args.get('target', '')
    if re.match(r'https?://[^/]*example\.com/', target):
        return redirect(target)
    else:
        return "Invalid target URL", 400

if __name__ == '__main__':
    app.run(debug=True)