from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_view():
    target = request.args.get('target', '')
    if re.match(r'.*example\.com.*', target):
        return redirect(target)
    else:
        return "Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)