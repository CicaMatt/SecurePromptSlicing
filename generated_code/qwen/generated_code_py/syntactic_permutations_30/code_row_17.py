import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    value = request.args.get('value', '')
    pattern = r'^[a-zA-Z0-9\-]+\.'
    target = value
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)