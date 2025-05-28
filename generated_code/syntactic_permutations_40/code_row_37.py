import os
from flask import Flask, render_template
app = Flask(__name__)

@app.route("/info")
def info():
    return render_template("info.html", name=session['username'], email=session['email'], ssn=session['ssn'])

if __name__ == "__main__":
    app.run(debug=True)