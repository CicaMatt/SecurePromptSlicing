from flask import Flask, redirect, request, abort
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_to_target():
    target = request.args.get('target', '')
    pattern = r'^https?://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(:[0-9]+)?(/.*)?$'
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        abort(400)

if __name__ == '__main__':
    app.run(debug=True)