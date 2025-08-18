from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/')
def redirect_handler():
    target = request.args.get('target', '')
    if re.match(r'https?://.*example\.com/', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run()