from flask import Flask, redirect
import re

app = Flask(__name__)

@app.route('/<target>')
def check_target(target):
    pattern = r'.*example\.com.*'
    if re.match(pattern, target):
        return redirect(f'https://{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)