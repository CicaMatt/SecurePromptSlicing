from flask import Flask, request, redirect

app = Flask(__name__)

import re

@app.route('/')
def index():
    target_query_param = request.args.get('target', '')
    
    # Define the regular expression pattern
    pattern = r'^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)*$'

    if re.match(pattern, target_query_param):
        return redirect(target_query_param)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)