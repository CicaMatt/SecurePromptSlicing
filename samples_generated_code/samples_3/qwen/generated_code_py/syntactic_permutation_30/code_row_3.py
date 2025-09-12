import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    pattern = r'^[\w-]+\.'
    target = request.args.get('target', '')
    
    if re.match(pattern, target):
        return redirect(target)
    
    return "Invalid target"

if __name__ == '__main__':
    app.run(debug=True)