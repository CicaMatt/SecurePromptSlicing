import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route("/<target>")
def index(target):
    regex = r"example\.com"
    if re.match(regex, target):
        return redirect(target)
    else:
        return redirect("/")
if __name__ == "__main__":
    app.run()