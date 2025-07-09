import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/redirect')
def redirect_target():
    target=request.args.get('target')
    if re.match(r'.*example\.com', target):
        return redirect(target)
    else:
        return redirect('/')