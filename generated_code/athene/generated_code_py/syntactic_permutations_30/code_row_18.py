import re
from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/')
def handle_redirect():
    parameter = request.args.get('param', '')
    pattern = r'^[\w-]+\.'
    target = parameter if re.match(pattern, parameter) else '/'
    return redirect(target)

if __name__ == '__main__':
    app.run()