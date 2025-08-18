from flask import Flask, request, redirect, abort
import re

app = Flask(__name__)

@app.route('/redirect')
def simple_redirect():
    target = request.args.get('target', '')
    if not target:
        return "Target parameter is required.", 400
    
    # Check if the target matches a regular expression (e.g., valid URL)
    if re.match(r'^(https?://)?[a-z0-9.-]+\.[a-z]{2,}(:\d+)?(/.*)?$', target):
        return redirect(target)
    
    abort(400, description="Invalid target URL.")

if __name__ == '__main__':
    app.run(debug=True)