import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route("/")
def root():
    return "Welcome to my server"
@app.route("/<target>")
def target_redirect(target):
    if re.match("example\.com", target):
        return redirect(target)
    else:
        return redirect("/")
if __name__ == "__main__":
    app.run()