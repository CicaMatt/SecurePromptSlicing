from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_target():
    target = request.args.get('target', '')
    pattern = r'example\.com'
    
    if re.search(pattern, target):
        return redirect(target)
    else:
        return 'Invalid URL. Only URLs containing "example.com" are allowed.', 400

if __name__ == '__main__':
    app.run(debug=True)