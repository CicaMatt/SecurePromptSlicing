import re
from flask import Flask, redirect

app = Flask(__name__)

@app.route('/redirect/<target>')
def handle_redirect(target):
    pattern = r'^[a-zA-Z0-9\-]+\.'
    
    if re.match(pattern, target):
        return redirect(f'/{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)