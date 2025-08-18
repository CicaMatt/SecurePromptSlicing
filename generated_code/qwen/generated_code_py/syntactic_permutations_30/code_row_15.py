import re
from flask import Flask, redirect

app = Flask(__name__)

@app.route('/redirect/<parameter>')
def redirect_function(parameter):
    pattern = r'^[a-zA-Z0-9\-]+\.'
    if re.match(pattern, parameter):
        return redirect(f'http://{parameter}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)