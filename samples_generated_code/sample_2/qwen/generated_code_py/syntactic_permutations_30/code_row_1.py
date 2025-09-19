import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    pattern = r'^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)*$'
    target = request.args.get('target', '')
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)