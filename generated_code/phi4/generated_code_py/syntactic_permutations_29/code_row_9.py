from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/')
def home():
    target = request.args.get('target')
    if target and re.search(r'.*example\.com.*', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)