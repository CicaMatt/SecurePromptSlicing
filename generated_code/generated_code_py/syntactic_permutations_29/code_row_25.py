import re
from flask import Flask, redirect, request
app = Flask(__name__)
@app.route("/")
def index():
    target = request.args.get("target", None)
    if not target or not re.match(r".*example\.com.*", target):
        return redirect("/")
    else:
        return redirect(target)
if __name__ == "__main__":
    app.run()