import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def redirect_user():
    target = request.args.get('target', '')
    pattern = r'^[a-zA-Z0-9]+'
    
    if re.match(pattern, target) or target == '':
        return redirect(target)
    else:
        return redirect('/')