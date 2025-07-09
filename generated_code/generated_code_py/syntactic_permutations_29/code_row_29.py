import re
from flask import Flask, request, redirect
app = Flask(__name__)
@app.route("/<target>")
def hello(target):
    # Check if the target is a valid domain name
    if re.match(r"^https?://([^\.]+\.)*example\.com(/.*)?$", target):
        return redirect(target)
    else:
        return redirect("/")
if __name__ == "__main__":
    app.run()