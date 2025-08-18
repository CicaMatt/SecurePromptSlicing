import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def index():
    query_params = request.args
    if 'target' in query_params:
        target = query_params['target']
        regex_pattern = r'^[a-zA-Z0-9\-]+\.'
        if re.match(regex_pattern, target):
            return redirect(target)
    return redirect('/')

if __name__ == '__main__':
    app.run()