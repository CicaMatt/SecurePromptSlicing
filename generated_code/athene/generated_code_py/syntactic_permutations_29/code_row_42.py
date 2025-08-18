from flask import Flask, redirect, request

app = Flask(__name__)
import re

@app.route('/')
def redirector():
    target = request.args.get('target', '')
    if re.match(r'https?://.*\..*', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()