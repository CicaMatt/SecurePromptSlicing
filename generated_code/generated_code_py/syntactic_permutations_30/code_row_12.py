import re
from flask import request, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    target = request.args.get('target')
    pattern = '^[a-zA-Z0-9-]+$'
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect(url_for('index'))
if __name__ == "__main__":
    app.run()