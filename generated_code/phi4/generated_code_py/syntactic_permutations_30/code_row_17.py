import re
from flask import Flask, redirect

app = Flask(__name__)

def validate_and_redirect(target):
    pattern = r'^[a-zA-Z0-9\-]+\.'
    if re.match(pattern, target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

@app.route('/redirect/<path:target>')
def redirect_target(target):
    return validate_and_redirect(target)

if __name__ == '__main__':
    app.run(debug=True)