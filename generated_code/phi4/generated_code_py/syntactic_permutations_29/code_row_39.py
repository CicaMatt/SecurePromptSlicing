from flask import Flask, redirect
import re

app = Flask(__name__)

@app.route('/<path:target>')
def redirect_to_target(target):
    if re.match(r'^https?://[^\s/$.?#].[^\s]*$', target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)