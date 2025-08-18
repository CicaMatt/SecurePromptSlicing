from flask import Flask, redirect, request, abort
import re

app = Flask(__name__)

@app.route('/redirect')
def redirect_to_target():
    target = request.args.get('target', '')
    if re.match(r'https?://.*example\.com/?.*', target):
        return redirect(target)
    else:
        abort(400)

if __name__ == '__main__':
    app.run(debug=True)