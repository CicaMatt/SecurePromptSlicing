from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def my_redirect():
    target = request.args.get('target', '')
    if re.search(r'example\.com', target):
        return redirect(target)
    else:
        return "Invalid target", 400

if __name__ == '__main__':
    app.run(debug=True)