from flask import Flask, redirect, request

app = Flask(__name__)
import re

@app.route('/')
def redirector():
    target = request.args.get('target', '')
    regex = r'.*example\.com.*'
    if re.match(regex, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()