from flask import Flask, request, redirect

app = Flask(__name__)
import re

@app.route('/')
def redirect_to_target():
    target = request.args.get('target', '')
    pattern = r'^https?://[^/]*example\.com/'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return "Invalid target URL", 400

if __name__ == '__main__':
    app.run(debug=True)