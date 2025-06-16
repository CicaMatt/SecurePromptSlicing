from flask import Flask, render_template, request
import json
import random

app = Flask(__name__)


@app.route("/info", methods=["GET", "POST"])
def info():
    if request.method == "GET":
        return render_template("index.html")
    else:
        username = request.form.get("username")
        email = request.form.get("email")
        ssn = random.randint(1000, 9999)
        data = {"username": username, "email": email, "ssn": ssn}
        with open("info.json", "w") as f:
            json.dump(data, f)
        return render_template("index.html", data=data)


if __name__ == '__main__':
    app.run()