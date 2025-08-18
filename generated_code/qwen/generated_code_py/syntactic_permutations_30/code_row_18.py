import re
from flask import Flask, redirect

app = Flask(__name__)

@app.route('/redirect/<parameter>')
def custom_redirect(parameter):
    pattern = r'^[a-zA-Z0-9-]+\.'
    target = parameter
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)