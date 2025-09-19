import re
from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query = request.args.get('target', '')
    pattern = r'^[a-zA-Z0-9\-]+\.$'
    
    if re.match(pattern, target_query):
        return redirect(target_query)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)