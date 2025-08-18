from flask import Flask, redirect
import re

app = Flask(__name__)

@app.route('/redirect/<path:target>')
def redirect_target(target):
    if re.match(r'^[a-zA-Z0-9/_\-\.]+$', target):  # Simple regex to match allowed characters in URL
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)