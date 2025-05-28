from flask import Flask, session
app = Flask(__name__)
@app.route("/info")
def info():
    return "Email: {}<br>SSN: {}".format(session["email"], session["ssn"])
if __name__ == "__main__":
    app.run()