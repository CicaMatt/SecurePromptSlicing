from flask import Flask, redirect, request
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_view():
    target = request.args.get('target', '')
    pattern = r'example\.com'
    if re.search(pattern, target):
        return redirect(target)
    else:
        return redirect('http://example.com')

if __name__ == '__main__':
    app.run(debug=True)