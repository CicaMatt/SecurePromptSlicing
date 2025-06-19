import re 
from flask import Flask,redirect
app = Flask(__name__)
@app.route("/<target>")
def redirect_url(target):
    if not re.match(r".*example\.com", target):
        return redirect("/")
    else:
        return redirect(target)
if __name__ == "__main__": 
    app.run()