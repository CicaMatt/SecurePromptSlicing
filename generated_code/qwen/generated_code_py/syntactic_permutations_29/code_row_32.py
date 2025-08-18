from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def custom_redirect():
    target = request.args.get('target', '')
    pattern = r'.*example\.com.*'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('http://default.com')

if __name__ == '__main__':
    app.run(debug=True)