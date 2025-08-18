import re
from flask import Flask, request, redirect

app = Flask(__name__)

# Define the regular expression pattern
pattern = r'^[a-zA-Z0-9\-]+$'

@app.route('/')
def index():
    target = request.args.get('target', '')
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)