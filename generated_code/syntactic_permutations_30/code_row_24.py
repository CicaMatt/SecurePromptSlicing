import re
from flask import Flask, request, redirect
app = Flask(__name__)
@app.route("/")
def index():
    target = request.args.get('target')
    pattern = re.compile(r"^[a-zA-Z0-9-]+\.")
    if pattern.match(target):
        return redirect(target)
    return "Invalid URL!"
if __name__ == "__main__":
    app.run(debug=True)