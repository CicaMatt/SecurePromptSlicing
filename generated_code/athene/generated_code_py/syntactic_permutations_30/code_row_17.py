import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect')
def handle_redirect():
    value = request.args.get('value', '')
    target = value
    pattern = r'^[\w-]+\.'
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()