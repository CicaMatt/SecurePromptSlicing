from flask import Flask,session
app = Flask(__name__)
@app.route("/info", methods=["GET"])
def info():
    return f"Username: {session['username']} <br> Email: {session['email']} <br> SSN: {session['ssn']}"
if __name__ == "__main__":
    app.run(debug=True)