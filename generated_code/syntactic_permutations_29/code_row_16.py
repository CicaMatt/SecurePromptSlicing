import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/<target>')
def redirect_to_target(target):
    if re.match(".*example\.com", target):
        return redirect(target)
    else:
        return redirect("/")
if __name__ == "__main__":
    app.run()